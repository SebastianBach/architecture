#include "image.h"
#include "image_data.h"
#include <cstring>

namespace image
{

class ImageStorage
{
public:
    ImageStorage(Pixel* data, unsigned int w, unsigned int h) : _data(data), _w(w), _h(h) {}

    ~ImageStorage() {}

    auto get_size() const
    {
        return _w * _h;
    }

    Pixel* const _data;
    const unsigned int _w;
    const unsigned int _h;
};
struct ImageDataInternal
{
    ImageDataInternal(Pixel* data, unsigned int w, unsigned int h) :_img(data, w, h) {}

    ImageStorage _img;
};

ImageDataInternal* cast(void* ptr)
{
    return static_cast<ImageDataInternal*>(ptr);
}

auto* alloc_image_data(unsigned int w, unsigned int h)
{
    const auto cnt  = w * h;
    auto* pixelData = new Pixel[cnt];

    auto* data = new ImageDataInternal{pixelData, w, h};

    for (auto i = 0u; i < cnt; ++i)
        data->_img._data[i] = {};

    return data;
}

void free_image_data(ImageDataInternal* img)
{
    delete[] img->_img._data;
    delete img;
}

ImageData::ImageData(unsigned int w, unsigned int h)
{
    _impl = alloc_image_data(w, h);
}

ImageData::~ImageData()
{
    free_image_data(cast(_impl));
}

Image* ImageData::get_image()
{
    auto* ptr = (void*)(&cast(_impl)->_img);
    return (Image*)ptr;
}

void ImageData::copy_from(ImageData* src)
{
    auto* src_img = cast(src->_impl);

    const auto src_size = src_img->_img.get_size();
    const auto dst_size = cast(_impl)->_img.get_size();

    if (src_size != dst_size)
    {
        free_image_data(cast(_impl));
        _impl = alloc_image_data(src_img->_img._w, src_img->_img._h);
    }

    std::memcpy(src_img->_img._data, cast(_impl)->_img._data, dst_size * sizeof(Pixel));
}

namespace
{
ImageStorage* cast_img(Image* ptr)
{
    return reinterpret_cast<ImageStorage*>(ptr);
}

const ImageStorage* cast_img(const Image* ptr)
{
    return reinterpret_cast<const ImageStorage*>(ptr);
}

const ImageStorage* cast_img_const(const Image* ptr)
{
    return reinterpret_cast<const ImageStorage*>(ptr);
}
} // namespace

unsigned int Image::get_width() const
{
    return cast_img_const(this)->_w;
}

unsigned int Image::get_height() const
{
    return cast_img_const(this)->_h;
}

Pixel* Image::get_line(unsigned int y)
{
    const auto w = get_width();
    return &(cast_img(this)->_data[w * y]);
}

const Pixel* Image::get_line(unsigned int y) const
{
    const auto w = get_width();
    return &(cast_img_const(this)->_data[w * y]);
}

void Image::fill(const Pixel& ref)
{
    const auto size = cast_img(this)->get_size();
    auto* data      = cast_img(this)->_data;
    for (auto i = 0u; i < size; ++i)
        data[i] = ref;
}

} // namespace image
