#pragma once

#include "pixel.h"

namespace image
{
class Image
{
public:
    unsigned int get_width() const;
    unsigned int get_height() const;

    Pixel* get_line(unsigned int y);
    const Pixel* get_line(unsigned int y) const;

    void fill(const Pixel&);

    template <typename T> void for_each_pixel(T& func)
    {
        const auto w = this->get_width();
        const auto h = this->get_height();

        for (auto y = 0u; y < h; ++y)
        {
            auto* data = this->get_line(y);
            for (auto x = 0u; x < w; ++x)
                func(data[x]);
        }
    }
};
} // namespace core
