#include "image_util.h"
#include "image.h"
#include <qimage.h>

namespace
{
inline unsigned char map(float v)
{
    if (v >= 1.0f)
        return 255u;
    if (v <= 0.0f)
        return 0u;
    return v * 255u;
};
} // namespace

namespace util
{

void convert_image(const image::Image& src, QImage& dst)
{
    const auto w = src.get_width();
    const auto h = src.get_height();

    dst = QImage{(int)w, (int)h, QImage::Format_RGB888};

    for (auto y = 0u; y < h; ++y)
    {
        const auto* src_line = src.get_line(y);
        auto* dst_line       = dst.scanLine(y);

        auto offset = 0u;

        for (auto x = 0u; x < w; ++x)
        {
            const auto& pixel = src_line[x];

            dst_line[offset]     = map(pixel.r);
            dst_line[offset + 1] = map(pixel.g);
            dst_line[offset + 2] = map(pixel.b);
            offset += 3;
        }
    }
}

} // namespace util