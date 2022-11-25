#include "config.h"
#include "config_standard.h"

namespace core
{
void add_deluxe_macros(Config& c)
{
    make_macro(c, "Inverted Checkerboard", CommandID{"cmd.fill.checkerboard"},
               CommandID{"cmd.filter.invert"});
}

void create_config(Config& c)
{
    c.width  = 1024;
    c.height = 512;

    fill_app_menu(c);
    fill_export_formats(c);
    fill_colors_menu(c);
    fill_default_buttons(c);
    fill_random(c);
    fill_filters(c);

    make_generic_button(CommandID{"cmd.fill.checkerboard"}, "Checkerboard", c);

    add_deluxe_macros(c);
}

} // namespace core
