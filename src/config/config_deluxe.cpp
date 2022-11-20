#include "config.h"
#include "config_standard.h"

namespace core
{

void add_deluxe_macros(Config& c)
{
    make_macro(c, "Inverted Checkerboard", CommandID{"cmd.fill.checkerboard"}, CommandID{"cmd.filter.invert"});
}

void create_config(Config& c)
{
    c.width  = 1024;
    c.height = 512;

    fill_default_menu(c);

    add_button(c, CommandID{"cmd.fill.checkerboard"}, "Checkerboard");

    add_deluxe_macros(c);
}

} // namespace core
