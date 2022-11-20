#include "config.h"
#include "config_standard.h"

namespace core
{

void create_config(Config& c)
{
    c.width  = 512;
    c.height = 512;

    fill_default_menu(c);
}

} // namespace core