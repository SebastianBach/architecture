#include "app_commands.h"
#include <cstring>
#include <map>
#include <string>

namespace core
{
using AppCommandMap = std::map<std::string, AppCommandFunction>;

auto& get_app_commands()
{
    static AppCommandMap storage;
    return storage;
}

void set_app_function(AppCommandID id, AppCommandFunction func)
{
    auto& commands   = get_app_commands();
    commands[id._id] = func;
}

ReturnVoid process_app_function(AppCommandID id)
{
    auto& commands = get_app_commands();
    auto it        = commands.find(id._id);
    if (it == commands.end())
        return Error("App Commmand ID not found", Error::TYPE::INVALID_ARG);

    return it->second();
}

} // namespace core
