#include "app_commands.h"
#include "process.h"
#include "ui_modules.h"
#include <qmenu.h>
#include <qmenubar.h>

namespace
{
void init_app_commands(MainWindow* window)
{
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

void run_app_command(core::AppCommandID id, MainWindow* window)
{
    window->add_to_log(id._id);

    const auto res = core::process_app_function(id);

    if (res.isError())
    {
        window->add_to_log(res.getError().msg);
        window->show_error_dialog(res.getError(), id._id);
    }
}

static auto res = add_ui_module(10u,
    [](window_data& data)
    {
        auto window        = data.window;
        const auto& config = data.config;
        auto bar           = data.bar;

        init_app_commands(window);

        auto app = new QMenu(window->tr("App"), window);
        bar->addMenu(app);

        for (const auto& command : config.appCommands)
        {
            auto action   = app->addAction(command.label);
            const auto id = command.id;
            window->connect(action, &QAction::triggered, [id, window]() { run_app_command(id, window); });
        }
    });
} // namespace

