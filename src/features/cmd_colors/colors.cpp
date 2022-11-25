#include "register.h"
#include "image.h"
#include "labels.h"

namespace
{
auto red(image::Image* img)
{
    img->fill({1.0f, 0.0f, 0.0f});

    return core::SUCCESS;
}

REGISTER_COMMAND(red, "cmd.fill.red", "Red");

auto green(image::Image* img)
{
    img->fill({0.0f, 1.0f, 0.0f});

    return core::SUCCESS;
}

REGISTER_COMMAND(green, "cmd.fill.green", "Green")

auto blue(image::Image* img)
{
    img->fill({0.0f, 0.0f, 1.0f});

    return core::SUCCESS;
}

REGISTER_COMMAND(blue, "cmd.fill.blue", "Blue")

auto white(image::Image* img)
{
    img->fill({1.0f, 1.0f, 1.0f});

    return core::SUCCESS;
}

REGISTER_COMMAND(white, "cmd.fill.white", "White")

auto black(image::Image* img)
{
    img->fill({0.0f, 0.0f, 0.0f});

    return core::SUCCESS;
}

REGISTER_COMMAND(black, "cmd.fill.black", "Black")
} // namespace
