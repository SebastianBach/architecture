#include "config.h"
#include "config_standard.h"

namespace core
{

void create_config(Config& c)
{
    c.width  = 512;
    c.height = 512;

    fill_app_menu(c);
    fill_export_formats(c);
    fill_colors_menu(c);
    fill_default_buttons(c);
    fill_random(c);
    fill_filters(c);
}

} // namespace core