#include "exports.h"
#include <cstring>
#include <map>

namespace
{
struct ExportIDCmp
{
    bool operator()(const core::ExportID& a, const core::ExportID& b) const
    {
        return std::strcmp(a._id, b._id) < 0;
    }
};

auto& get_exporters()
{
    static std::map<core::ExportID, core::ExportFunction, ExportIDCmp>
        exporters;
    return exporters;
}

} // namespace

namespace core
{

void add_export(ExportID id, ExportFunction func)
{
    get_exporters()[id] = func;
}

void get_export_formats(std::vector<ExportID>& ids)
{
    const auto& exporters = get_exporters();
    ids.reserve(exporters.size());

    for (auto it = exporters.begin(); it != exporters.end(); it++)
        ids.push_back(it->first);
}

ReturnVoid export_image(ExportID id, const char* path, image::Image& img)
{
    if (path == nullptr)
        return Error{"Invalid path argument.", core::Error::TYPE::INVALID_ARG};

    const auto& exporters = get_exporters();

    if (exporters.empty())
        return Error{"No export formats available.",
                     core::Error::TYPE::INVALID_STATE};

    auto it = exporters.find(id);

    if (it == exporters.end())
        return Error{"Exporter ID not found.", core::Error::TYPE::INVALID_ARG};

    auto& func = it->second;

    if (!func)
        return Error{"Invalid export function.",
                     core::Error::TYPE::INVALID_STATE};

    return func(path, img);
}

} // namespace core
