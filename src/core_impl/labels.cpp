#include "labels.h"
#include <map>
#include <string>

namespace
{
auto& get_labels()
{
    static std::map<std::string, const char*> labels;
    return labels;
}
} // namespace

namespace core
{
void add_label(const char* id, const char* label)
{
    if (id != nullptr && label != nullptr)
    {
        auto& labels = get_labels();
        labels[id]   = label;
    }
}

const char* get_label(const char* id, const char* fallback)
{
    static const char* empty = "???";

    if (id == nullptr)
        return empty;

    auto& labels = get_labels();
    auto it      = labels.find(id);

    // label found
    if (it != labels.end())
        return it->second;
  
    // nothing found

    if (fallback)
        return fallback;

    return empty;
}

} // namespace core
