#pragma once
#include "error.h"
#include <functional>
#include <vector>

namespace image
{
class Image;
}

namespace core
{
struct ExportID
{
    explicit ExportID(const char* id, const char* suffix) : _id(id), _suffix(suffix) {}
    const char* const _id;
    const char* const _suffix;
};


using ExportFunction = std::function<ReturnVoid(const char*, image::Image&)>;

void add_export(ExportID, ExportFunction);

void get_export_formats(std::vector<ExportID>& ids);

ReturnVoid export_image(ExportID, const char*, image::Image&);


} // namespace core
