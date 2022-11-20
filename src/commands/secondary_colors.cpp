#include "register.h"
#include "image.h"

namespace
{
core::ReturnVoid yellow(image::Image* img)
{
    img->fill({1.0f, 1.0f, 0.0f});

    return core::SUCCESS;
}

REGISTER_COMMAND(yellow, "cmd.fill.yellow", "Yellow")


core::ReturnVoid cyan(image::Image* img)
{
    img->fill({0.0f, 1.0f, 1.0f});

    return core::SUCCESS;
}

REGISTER_COMMAND(cyan, "cmd.fill.cyan", "Cyan")


core::ReturnVoid magenta(image::Image* img)
{
    img->fill({1.0f, 0.0f, 1.0f});

    return core::SUCCESS;
}

REGISTER_COMMAND(magenta, "cmd.fill.magenta", "Magenta")
} // namespace
