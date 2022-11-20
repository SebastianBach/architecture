#include "process.h"
#include "register.h"
#include <cstring>
#include <string>
#include <vector>

namespace core
{
struct Command
{
    CommandFunc _process;
    CommandID _id;
};

struct CommandStorage
{
    CommandStorage()
    {
        _storage.reserve(1024);
    }

    std::vector<Command> _storage;
};

auto& get_commands()
{
    static CommandStorage commands;
    return commands._storage;
}

bool register_command(CommandFunc process, CommandID id)
{
    get_commands().push_back({process, id});
    return true;
}

ReturnVoid process_command(const CommandID& id, image::Image* img)
{
    if (img == nullptr)
        return Error{"Invalid Image pointer.", Error::TYPE::INVALID_ARG};

    auto& cmds = get_commands();

    if (cmds.empty())
        return Error{"No Commands avaiable.", Error::TYPE::INVALID_STATE};

    for (auto& cmd : cmds)
    {
        if (std::strcmp(id._id, cmd._id._id) == 0)
        {
            if (cmd._process)
                return cmd._process(img);
            else
                return Error{"Invalid Process Function.", Error::TYPE::INVALID_STATE};
        }
    }

    return Error{"Command ID not found.", Error::TYPE::INVALID_ARG};
}

void get_commands(std::vector<CommandID>& commands_ids, const char* filter)
{
    const auto& commands = get_commands();

    if (filter == nullptr)
    {
        commands_ids.reserve(commands.size());

        for (const auto& cmd : commands)
            commands_ids.push_back(cmd._id);
    }
    else
    {
        for (const auto& cmd : commands)
            if (std::string(cmd._id._id).find(filter) != std::string::npos)
                commands_ids.push_back(cmd._id);
    }
}

} // namespace core
