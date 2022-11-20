#pragma once

namespace image
{
class Image;

class ImageData
{
public:

    ImageData(unsigned int width, unsigned int height);
    ~ImageData();

    Image* get_image();

    void copy_from(ImageData*);

private:
    void* _impl;
};
}

