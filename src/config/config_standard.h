#pragma once

#include "config.h"
#include "labels.h"
#include "process.h"
#include "app_commands.h"

namespace core
{

inline void add_button(Config& c, const CommandID& id, const char* label = nullptr)
{
    if (label == nullptr)
        label = core::get_label(id._id);

    c.buttons.push_back({id, label});
}

inline void add_menu_entry(menu_element& e, const CommandID& id, const char* label = nullptr)
{
    if (label == nullptr)
        label = core::get_label(id._id);

    e.commands.push_back({id, label});
}

inline void fill_default_menu(Config& c)
{
    c.appCommands.push_back({AppCommandID{"app.cmd.close"}, "Close"});

    add_button(c, CommandID{"cmd.fill.red"}, "Fill Red");
    add_button(c, CommandID{"cmd.fill.green"}, "Fill Green");
    add_button(c, CommandID{"cmd.fill.blue"}, "Fill Blue");

    {
        menu_element colors;
        colors.name = "Colors";
        add_menu_entry(colors, CommandID{"cmd.fill.black"});
        add_menu_entry(colors, CommandID{"cmd.fill.white"});
        add_menu_entry(colors, CommandID{"cmd.fill.red"});
        add_menu_entry(colors, CommandID{"cmd.fill.green"});
        add_menu_entry(colors, CommandID{"cmd.fill.blue"});
        add_menu_entry(colors, CommandID{"cmd.fill.magenta"});
        add_menu_entry(colors, CommandID{"cmd.fill.cyan"});
        add_menu_entry(colors, CommandID{"cmd.fill.yellow"});

        c.menu.push_back(colors);
    }

    {
        menu_element noise;
        noise.name = "Noise";
        noise.commands.push_back({CommandID{"cmd.fill.random_color"}, "RGB Noise"});
        noise.commands.push_back({CommandID{"cmd.fill.random_grey"}, "Grey Noise"});
        noise.commands.push_back({CommandID{"cmd.fill.random_bw"}, "Black and White"});
        c.menu.push_back(noise);
    }

    {
        menu_element patterns;
        patterns.name = "Patterns";
        add_menu_entry(patterns, CommandID{"cmd.fill.checkerboard"});
        c.menu.push_back(patterns);
    }

    {
        menu_element filters;
        filters.name = "Filters";

        // search for filters
        std::vector<core::CommandID> ids;
        core::get_commands(ids, "cmd.filter.");

        for (auto& id : ids)
            add_menu_entry(filters, id);

        c.menu.push_back(filters);
    }
}
} // namespace core
