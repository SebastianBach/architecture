#pragma once

#include "app_commands.h"
#include "exports.h"
#include "labels.h"
#include "register.h"
#include <variant>
#include <vector>

namespace core
{
struct app_command
{
    AppCommandID id;
    const char* label;
};

using CommandHolder = std::variant<AppCommandID, CommandID, ExportID>;

enum class COMMAND
{
    IMAGE,
    APP,
    EXPORTER
};

class GenericCommand : public CommandHolder
{
public:
    template <typename T>
    GenericCommand(const T& id, const char* label)
        : CommandHolder(id), _label(label)
    {
    }

    COMMAND get_type() const
    {
        if (std::holds_alternative<AppCommandID>(*this))
            return COMMAND::APP;

        if (std::holds_alternative<CommandID>(*this))
            return COMMAND::IMAGE;

        return COMMAND::EXPORTER;
    }

    template <typename T> explicit operator T() const
    {
        return std::get<T>(*this);
    }

    auto get_id() const
    {
        if (std::holds_alternative<AppCommandID>(*this))
            return std::get<AppCommandID>(*this)._id;

        if (std::holds_alternative<CommandID>(*this))
            return std::get<CommandID>(*this)._id;

        return std::get<ExportID>(*this)._id;
    }

    auto get_label() const
    {
        return _label;
    }

private:
    const char* _label;
};

struct generic_menu_element
{
    generic_menu_element()
    {
        commands.reserve(16);
    }

    const char* name = nullptr;
    std::vector<GenericCommand> commands;
};

struct macro
{
    const char* name = nullptr;
    std::vector<CommandID> commands;
};

struct Config
{
    Config()
    {
        macros.reserve(16);
    }

    bool ui_show_log = false;

    std::vector<generic_menu_element> generic_menus;

    std::vector<GenericCommand> generic_buttons;

    std::vector<macro> macros;

    unsigned int width  = 512;
    unsigned int height = 512;
};

template <typename T>
void make_generic_button(const T& cmd, const char* label, Config& c)
{
    c.generic_buttons.push_back({cmd, label});
}

template <typename T>
void add_to_menu(const T& cmd, const char* label, generic_menu_element& menu)
{
    menu.commands.push_back({cmd, label});
}

template <typename... ARGS>
void make_macro(Config& c, const char* label, ARGS... args)
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