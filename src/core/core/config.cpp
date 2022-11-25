#include "config.h"

namespace
{
core::Config _create_config()
{
    core::Config c;
    core::create_config(c);
    return c;
}
} // namespace

namespace core
{
const Config& get_config()
{
    static const Config c{_create_config()};
    return c;
}
} // namespace core