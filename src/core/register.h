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

#define REGISTER_COMMAND(FUNC, ID, LABEL)                                                                                     \
    namespace                                                                                                          \
    {                                                                                                                  \
    static const auto res_##FUNC = []()                                                                                \
    {                                                                                                                  \
        core::register_command(FUNC, core::CommandID{ID});                                                             \
        core::add_label(ID, LABEL);                                                                                    \
        return true;                                                                                                   \
    }();                                                                                                               \
    }

} // namespace core
