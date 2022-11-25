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

static auto res = add_ui_module(0u, [](window_data& data)
                                { init_app_commands(data.window); });
} // namespace
