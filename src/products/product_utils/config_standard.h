#pragma once

#include "app_commands.h"
#include "config.h"
#include "labels.h"
#include "process.h"

namespace core
{
inline void fill_default_buttons(Config& c)
{
    make_generic_button(CommandID{"cmd.fill.red"}, "Fill Red", c);
    make_generic_button(CommandID{"cmd.fill.green"}, "Fill Green", c);
    make_generic_button(CommandID{"cmd.fill.blue"}, "Fill Blue", c);
}

inline void fill_colors_menu(Config& c)
{
    generic_menu_element colors;
    colors.name = "Colors";
    add_to_menu(CommandID{"cmd.fill.red"}, "Red", colors);
    add_to_menu(CommandID{"cmd.fill.green"}, "Green", colors);
    add_to_menu(CommandID{"cmd.fill.blue"}, "Blue", colors);
    add_to_menu(CommandID{"cmd.fill.magenta"}, "Magenta", colors);
    add_to_menu(CommandID{"cmd.fill.yellow"}, "Yellow", colors);
    add_to_menu(CommandID{"cmd.fill.cyan"}, "Cyan", colors);
    add_to_menu(CommandID{"cmd.fill.black"}, "Black", colors);
    add_to_menu(CommandID{"cmd.fill.white"}, "White", colors);
    c.generic_menus.push_back(colors);
}

inline void fill_app_menu(Config& c)
{
    generic_menu_element menu;
    menu.name = "App";
    add_to_menu(AppCommandID{"app.cmd.close"}, "Close", menu);
    c.generic_menus.push_back(menu);
}

inline void fill_export_formats(Config& c)
{
    std::vector<core::ExportID> ids;
    core::get_export_formats(ids);

    if (ids.empty())
        return;

    generic_menu_element exports;
    exports.name = "Export";

    for (auto& id : ids)
        add_to_menu(id, id._suffix, exports);

    c.generic_menus.push_back(exports);
}

inline void fill_filters(Config& c)
{
    // search for filters
    std::vector<core::CommandID> ids;
    core::get_commands(ids, "cmd.filter.");

    if (ids.empty())
        return;

    generic_menu_element filters;
    filters.name = "Filters";

    for (auto& id : ids)
        add_to_menu(id, get_label(id._id), filters);

    c.generic_menus.push_back(filters);
}

inline void fill_random(Config& c)
{
    generic_menu_element noise;
    noise.name = "Noise";
    add_to_menu(CommandID{"cmd.fill.random_color"}, "RGB Noise", noise);
    add_to_menu(CommandID{"cmd.fill.random_grey"}, "Grey Noise", noise);
    add_to_menu(CommandID{"cmd.fill.random_bw"}, "Black and White", noise);
    c.generic_menus.push_back(noise);
}
} // namespace core
