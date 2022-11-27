#include "exports.h"
#include "image.h"
#include "image_util.h"
#include <qimage.h>

namespace
{
core::ReturnVoid export_png(const char* file, image::Image& img)
{
    QImage qimage;

    util::convert_image(img, qimage);

    const auto res = qimage.save(file, "PNG");

    if (!res)
        return core::Error{"Error saving PNG file."};

    return core::SUCCESS;
}

static const auto res = []()
{
    core::add_export(core::ExportID{"export.png", "png"}, export_png);
    return true;
}();
} // namespace
