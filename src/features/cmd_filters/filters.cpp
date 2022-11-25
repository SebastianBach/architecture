#include "register.h"
#include "image.h"

namespace
{
core::ReturnVoid invert(image::Image* img)
{
    img->for_each_pixel(
        [](image::Pixel& p)
        {
            p.r = 1.0f - p.r;
            p.g = 1.0f - p.g;
            p.b = 1.0f - p.b;
        });

    return core::SUCCESS;
}

REGISTER_COMMAND(invert, "cmd.filter.invert", "Invert")

} // namespace
