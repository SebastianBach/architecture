#include "app.h"
#include "app_commands.h"
#include "config.h"
#include "exports.h"
#include "image_data.h"
#include "main_window.h"
#include "process.h"
#include "ui_modules.h"
#include "utility.h"
#include <QMessageBox>
#include <qdebug.h>
#include <qfiledialog.h>

namespace
{
core::ReturnVoid execute_image_command(const core::GenericCommand& command,
                                       MainWindow*                 window,
                                       image::ImageData*           image)
{
    const auto cmdID = static_cast<core::CommandID>(command);
    const auto res   = core::process_command(cmdID, image->get_image());

    if (res)
        window->update_display();

    return res;
}

core::ReturnVoid execute_app_command(const core::GenericCommand& command,
                                     MainWindow*, image::ImageData*)
{
    return core::process_app_function(static_cast<core::AppCommandID>(command));
}

core::ReturnVoid execute_exporter_command(const core::GenericCommand& command,
                                          MainWindow*                 window,
                                          image::ImageData*           image)
{
    const auto id = static_cast<core::ExportID>(command);

    auto filter = "Image File (*." + QString(id._suffix) + ")";

    const auto file = QFileDialog::getSaveFileName(nullptr, "Save Image", "",
                                                   filter, &filter);
    if (file.isEmpty())
        return core::SUCCESS;

    const auto stdString = file.toStdString();
    auto       filename  = stdString.c_str();

    window->add_to_log(filename);

    return core::export_image(id, filename, *(image->get_image()));
}

core::ReturnVoid execute_command(const core::GenericCommand& command,
                                 MainWindow* window, image::ImageData* image)
{
    using MAP_FUNC =
        std::map<core::COMMAND, std::function<core::ReturnVoid(
                                    const core::GenericCommand& command,
                                    MainWindow* window, image::ImageData*)>>;

    static const MAP_FUNC map = []()
    {
        MAP_FUNC funcs;
        funcs[core::COMMAND::IMAGE]  = execute_image_command;
        funcs[core::COMMAND::APP]    = execute_app_command;
        funcs[core::COMMAND::EXPORTER] = execute_exporter_command;

        return funcs;
    }();

    const auto type = command.get_type();
    return map.at(type)(command, window, image);
}

} // namespace

namespace app
{
App::App(int argc, char* argv[]) : _config(core::get_config())
{
    _app    = std::make_unique<QApplication>(argc, argv);
    _image  = std::make_unique<image::ImageData>(_config.width, _config.height);
    _window = std::make_unique<MainWindow>(*_image.get()->get_image());

    create_ui_modules(this, _window.get(), _window.get()->_menuBar,
                      _window.get()->_buttons, _config);

    setup_app_commands();

    if (argc > 1 && QString(argv[1]) == QString("test"))
        setup_testing();

    _window.get()->showMaximized();
}

int App::run()
{
    return _app.get()->exec();
}

void App::run_command(const core::GenericCommand& command)
{
    auto* window = _window.get();

    const char* id = command.get_id();
    window->add_to_log(id);

    const auto res = execute_command(command, window, _image.get());

    if (res.isError())
    {
        window->add_to_log(res.getError().msg);
        handle_error(res.getError(), id);
    }
}

void App::run_macro(const core::macro& macro)
{
    auto* window = _window.get();
    window->add_to_log(macro.name);

    for (const auto& cmd : macro.commands)
    {
        window->add_to_log(cmd._id);

        auto res = core::process_command(cmd, _image.get()->get_image());

        if (res.isError())
        {
            window->add_to_log(res.getError().msg);
            handle_error(res.getError(), cmd._id);
            return;
        }
    }

    window->update_display();
}

void App::handle_error(const core::Error& error, const char* id)
{
    if (_testmode)
    {
        qCritical() << "Error int test mode: " << error.msg << " " << id;
        exit(1);
        return;
    }

    QString msg{"Error executing command "};
    msg += id;
    msg += "\n";
    msg += convert_error(error);

    QMessageBox::critical(nullptr, "Error", msg);
}

void App::setup_app_commands()
{
    auto* window = _window.get();

    core::set_app_function(core::AppCommandID{"app.cmd.close"},
                           [window]()
                           {
                               window->close();
                               return core::SUCCESS;
                           });

    core::set_app_function(core::AppCommandID{"app.cmd.redraw"},
                           [window]()
                           {
                               window->update_display();
                               return core::SUCCESS;
                           });
}
void App::setup_testing()
{
    _testmode = true;

    // store commands to test
    for (const auto& menu : _config.generic_menus)
        for (const auto& command : menu.commands)
            if (command.get_type() == core::COMMAND::IMAGE)
                _testCommands.push(static_cast<core::CommandID>(command));

    for (const auto& macro : _config.macros)
        for (const auto command : macro.commands)
            _testCommands.push(command);

    for (const auto& command : _config.generic_buttons)
        if (command.get_type() == core::COMMAND::IMAGE)
            _testCommands.push(static_cast<core::CommandID>(command));

    _timer = std::make_unique<QTimer>(this);

    this->connect(_timer.get(), &QTimer::timeout, this, &App::test);

    _timer.get()->start(250);
}

void App::exit(int value)
{
    _window.get()->close();
    _app.get()->exit(value);
}

void App::test()
{
    if (_testCommands.empty())
    {
        _timer.get()->stop();

        qInfo() << "test success";
        exit(0);
        return;
    }

    const auto cmd = _testCommands.front();

    run_command(core::GenericCommand{cmd, ""});

    _testCommands.pop();
}

} // namespace app
