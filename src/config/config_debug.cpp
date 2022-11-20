#include "config.h"
#include "config_standard.h"

namespace core
{
void create_config(Config& c)
{
    c.ui_show_log = true;

    c.buttons.push_back({CommandID{"cmd.dev.error"}, "Trigger Error"});

    fill_default_menu(c);

    {
        menu_element dev;
        dev.name = "DEVELOPER";
        dev.commands.push_back({CommandID{"cmd.dev.error"}, "Trigger Error"});
        dev.commands.push_back({CommandID{"totally.invalid.id"}, "Invalid Command"});
        c.menu.push_back(dev);
    }

    {
        menu_element all_commands;
        all_commands.name = "All Commands";

        std::vector<core::CommandID> ids;
        core::get_commands(ids);

        for (const auto& id : ids)
            add_menu_entry(all_commands, id);

        c.menu.push_back(all_commands);
    }

    make_macro(c, "Invalid Macro", CommandID{"cmd.fill.red"}, CommandID{"totally.invalid.id"});

    c.appCommands.push_back({AppCommandID{"app.cmd.redraw"}, "Redraw"});

    c.width  = 1024;
    c.height = 512;
}

} // namespace core
