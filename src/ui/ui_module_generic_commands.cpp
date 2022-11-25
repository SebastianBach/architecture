#include "process.h"
#include "ui_modules.h"
#include <qfiledialog.h>
#include <qmenu.h>
#include <qmenubar.h>

namespace
{
core::ReturnVoid execute_image_command(const core::GenericCommand& command,
                                       MainWindow* window)
{
    const auto cmdID = static_cast<core::CommandID>(command);
    const auto res   = core::process_command(cmdID, window->_data->get_image());

    if (res)
        window->update_display();

    return res;
}

core::ReturnVoid execute_app_command(const core::GenericCommand& command,
                                     MainWindow*)
{
    return core::process_app_function(static_cast<core::AppCommandID>(command));
}

core::ReturnVoid execute_exporter_command(const core::GenericCommand& command,
                                          MainWindow* window)
{
    const auto id = static_cast<core::ExportID>(command);

    auto filter = "Image File (*." + QString(id._suffix) + ")";

    const auto file = QFileDialog::getSaveFileName(nullptr, "Save Image", "",
                                                   filter, &filter);
    if (file.isEmpty())
        return core::SUCCESS;

    const auto stdString = file.toStdString();
    auto filename        = stdString.c_str();

    window->add_to_log(filename);

    return core::export_image(id, filename, *(window->_data->get_image()));
}

core::ReturnVoid execute_command(const core::GenericCommand& command,
                                 MainWindow* window)
{
    using MAP_FUNC =
        std::map<core::COMMAND,
                 std::function<core::ReturnVoid(
                     const core::GenericCommand& command, MainWindow* window)>>;

    static const MAP_FUNC map = []()
    {
        MAP_FUNC map;
        map[core::COMMAND::IMAGE]    = execute_image_command;
        map[core::COMMAND::APP]      = execute_app_command;
        map[core::COMMAND::EXPORTER] = execute_exporter_command;

        return map;
    }();

    const auto type = command.get_type();
    return map.at(type)(command, window);
}

void run_generic_command(const core::GenericCommand& command,
                         MainWindow* window)
{
    const char* id = command.get_id();
    window->add_to_log(id);

    const auto res = execute_command(command, window);

    if (res.isError())
    {
        window->add_to_log(res.getError().msg);
        window->show_error_dialog(res.getError(), id);
    }
}

static auto res = add_ui_module(
    21u,
    [](window_data& data)
    {
        auto window        = data.window;
        const auto& config = data.config;
        auto bar           = data.bar;

        for (const auto& menu_element : config.generic_menus)
        {
            auto entry = new QMenu(window->tr(menu_element.name), window);
            bar->addMenu(entry);

            for (const auto& command : menu_element.commands)
            {
                auto action = entry->addAction(command.get_label());

                window->connect(action, &QAction::triggered,
                                [&command, window]()
                                { run_generic_command(command, window); });
            }
        }
    });

static auto resbuttons = add_ui_module(
    50u,
    [](window_data& data)
    {
        auto window        = data.window;
        const auto& config = data.config;
        auto bar           = data.bar;
        auto grid          = data.button_area;

        auto offset       = 10;
        auto buttonOffset = 0;
        for (const auto& id : config.generic_buttons)
        {
            auto* button = new QPushButton(id.get_label(), window);
            button->setMinimumSize(QSize(200, 50));
            button->setMaximumSize(QSize(200, 50));
            offset += 50;

            grid->addWidget(button, buttonOffset, 0, Qt::AlignTop);
            buttonOffset++;

            window->connect(button, &QPushButton::released, window,
                            [&id, window]()
                            { run_generic_command(id, window); });
        }
    });

} // namespace
