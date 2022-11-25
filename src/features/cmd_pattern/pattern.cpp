#include "image.h"
#include "register.h"
#include <cstdlib>
#include <ctime>

namespace
{
core::ReturnVoid checkerboard(image::Image* img)
{
    const auto w = img->get_width();
    const auto h = img->get_height();

    for (auto y = 0u; y < h; ++y)
    {
        auto* data = img->get_line(y);
        for (auto x = 0u; x < w; ++x)
        {
            const auto a = x % 40 > 20 ? 1.0f : 0.0f;
            const auto v = y % 40 > 20 ? 1.f - a : a;

            data[x].r = v;
            data[x].g = v;
            data[x].b = v;
        }
    }

    return core::SUCCESS;
}

REGISTER_COMMAND(checkerboard, "cmd.fill.checkerboard", "Checkerboard")

} // namespace
