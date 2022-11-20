#include "config.h"
#include "config_standard.h"

namespace core
{
void create_config(Config& c)
{
    add_button(c, CommandID{"cmd.fill.red"}, "Fill Red");
    add_button(c, CommandID{"cmd.fill.green"}, "Fill Green");
    add_button(c, CommandID{"cmd.fill.blue"}, "Fill Blue");

    menu_element colors;
    colors.name = "Colors";
    add_menu_entry(colors, CommandID{"cmd.fill.black"}, "Black");
    add_menu_entry(colors, CommandID{"cmd.fill.white"}, "White");
    add_menu_entry(colors, CommandID{"cmd.fill.red"}, "Red");
    add_menu_entry(colors, CommandID{"cmd.fill.green"}, "Green");
    add_menu_entry(colors, CommandID{"cmd.fill.blue"}, "Blue");
    add_menu_entry(colors, CommandID{"cmd.fill.magenta"}, "Magenta");
    add_menu_entry(colors, CommandID{"cmd.fill.cyan"}, "Cyan");
    add_menu_entry(colors, CommandID{"cmd.fill.yellow"}, "Yellow");

    c.menu.push_back(colors);

    c.appCommands.push_back({AppCommandID{"app.cmd.close"}, "Close"});

    c.width  = 512;
    c.height = 512;
}

} // namespace core
