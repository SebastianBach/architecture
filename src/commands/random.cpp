#include "image.h"
#include "register.h"
#include <cstdlib>
#include <ctime>

namespace
{
static constexpr auto rand_max_f = float(RAND_MAX);

core::ReturnVoid random_colors(image::Image* img)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    img->for_each_pixel(
        [](image::Pixel& pixel)
        {
            pixel.r = float(rand()) / rand_max_f;
            pixel.g = float(rand()) / rand_max_f;
            pixel.b = float(rand()) / rand_max_f;
        });

    return core::SUCCESS;
}

REGISTER_COMMAND(random_colors, "cmd.fill.random_color", "Random Color")

core::ReturnVoid random_grey(image::Image* img)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    img->for_each_pixel(
        [](image::Pixel& pixel)
        {
            const auto value = float(rand()) / rand_max_f;
            pixel.r          = value;
            pixel.g          = value;
            pixel.b          = value;
        });

    return core::SUCCESS;
}

REGISTER_COMMAND(random_grey, "cmd.fill.random_grey", "Random Grey")

core::ReturnVoid random_bw(image::Image* img)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    img->for_each_pixel(
        [](image::Pixel& pixel)
        {
            const auto rnd   = float(rand()) / rand_max_f;
            const auto value = rnd >= 0.5f ? 1.0f : 0.0f;

            pixel.r = value;
            pixel.g = value;
            pixel.b = value;
        });

    return core::SUCCESS;
}

REGISTER_COMMAND(random_bw, "cmd.fill.random_bw", "Random Black and White")

} // namespace
