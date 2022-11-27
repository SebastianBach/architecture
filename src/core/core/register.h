#pragma once
#include "error.h"
#include "labels.h"
#include <functional>

namespace image
{
class Image;
}

namespace core
{
struct CommandID
{
    explicit CommandID(const char* id) : _id(id) {}

    const char* const _id;
};

using CommandFunc = std::function<ReturnVoid(image::Image*)>;

bool register_command(CommandFunc, CommandID);

#define REGISTER_COMMAND(FUNC, ID, LABEL)                                      \
    static_assert(sizeof(ID) > 1, "command ID must not be empty.");            \
    static_assert(sizeof(LABEL) > 1, "command label must not be empty.");      \
    static_assert(FUNC != nullptr, "command function must not be empty.");     \
    namespace                                                                  \
    {                                                                          \
    static const auto res_##FUNC = []()                                        \
    {                                                                          \
        core::register_command(FUNC, core::CommandID{ID});                     \
        core::add_label(ID, LABEL);                                            \
        return true;                                                           \
    }();                                                                       \
    }

} // namespace core
