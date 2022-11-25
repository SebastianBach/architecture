#pragma once

class QImage;
namespace image
{
class Image;
}

namespace util
{
void convert_image(const image::Image& src, QImage& dst);
}
