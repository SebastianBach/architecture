#include "config.h"
#include "config_standard.h"
#include "process.h"

namespace core
{
void create_config(Config& c)
{
    c.ui_show_log = true;

    make_generic_button(CommandID{"cmd.dev.error"}, "Trigger Error", c);

    fill_app_menu(c);
    fill_export_formats(c);
    fill_colors_menu(c);
    fill_default_buttons(c);
    fill_random(c);
    fill_filters(c);

    {
        generic_menu_element dev;
        dev.name = "DEVELOPER";
        add_to_menu(CommandID{"cmd.dev.error"}, "Trigger Error", dev);
        add_to_menu(CommandID{"totally.invalid.id"}, "Invalid Command", dev);
        add_to_menu(AppCommandID{"totally.invalid.id"}, "Invalid App Command",
                    dev);
        add_to_menu(AppCommandID{"app.cmd.redraw"}, "Redraw", dev);
        c.generic_menus.push_back(dev);
    }

    {
        generic_menu_element all_commands;
        all_commands.name = "All Commands";

        std::vector<core::CommandID> ids;
        core::get_commands(ids);

        for (const auto& id : ids)
            add_to_menu(id, get_label(id._id), all_commands);

        c.generic_menus.push_back(all_commands);
    }

    make_macro(c, "Invalid Macro", CommandID{"cmd.fill.red"},
               CommandID{"totally.invalid.id"});

    c.width  = 1024;
    c.height = 512;
}

} // namespace core
