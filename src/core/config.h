#pragma once

#include "app_commands.h"
#include "register.h"
#include <vector>

namespace core
{

struct app_command
{
    AppCommandID id;
    const char* label;
};

struct menu_command
{
    CommandID id;
    const char* label;
};

struct menu_element
{
    menu_element()
    {
        commands.reserve(16);
    }

    const char* name = nullptr;
    std::vector<menu_command> commands;
};

struct macro
{
    const char* name = nullptr;
    std::vector<CommandID> commands;
};

struct button
{
    CommandID command;
    const char* name;
};

struct Config
{
    Config()
    {
        menu.reserve(16);
        buttons.reserve(16);
        appCommands.reserve(16);
        macros.reserve(16);
    }

    bool ui_show_log = false;

    std::vector<menu_element> menu;

    std::vector<button> buttons;

    std::vector<macro> macros;

    std::vector<app_command> appCommands;

    unsigned int width  = 512;
    unsigned int height = 512;
};

template <typename... ARGS> void make_macro(Config& c, const char* label, ARGS... args)
{
    macro m;
    m.name = label;

    const auto list = std::initializer_list<CommandID>{args...};

    m.commands.reserve(list.size());

    for (const auto& element : list)
        m.commands.push_back(element);

    c.macros.push_back(m);
}

void create_config(Config&);

const Config& get_config();

} // namespace core