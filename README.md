# Architecture Playground

Playground for some (C++) software architecture ideas.
More detailed documentation will be added in the future.

# Dependencies

- QT5 (https://www.qt.io/)
- Google Test (https://github.com/google/googletest); will be installed by CMake

# Build

Build with *CMake*:

```
mkdir build
cd build
cmake .. -DQt5_DIR=C:/my_qt_5_install/msvc2017_64/lib/cmake/Qt5 
cmake --build .
ctest

```


# Domains
## Core & Utility

The core allows new functions to be registered and provides access to those functions.
Extending the core means that new types of functions can be handled.

## Features

New functions can be implemented and made available by registering them in the core.
For example, adding a new image operation means implementing such a function in a function library:

```
auto grey(image::Image* img)
{
    img->fill({0.5f, 0.5f, 0.5f});

    return core::SUCCESS;
}

REGISTER_COMMAND(grey, "cmd.fill.grey", "Grey");
```

## Product Design

Products are designed by composing features.
Basic product settings (name, version, file name) are defined with CMake:

```
add_executable(app_product_new)
make_generic_app("The New Product" ${PRODUCT_VERSION} "product_new" config_product_new.cpp app_product_new)
use_qt_ui(app_product_new)
target_link_libraries(app_product_new PRIVATE lib_cmd_colors)
target_link_libraries(app_product_new PRIVATE lib_cmd_filters)
target_link_libraries(app_product_new PRIVATE lib_cmd_random)
target_link_libraries(app_product_new PRIVATE lib_cmd_pattern)
target_link_libraries(app_product_new PRIVATE lib_exports)
```

If a certain feature library is not linked to the product, the corresponding features are not available.
E.g. a demo version is simply created by using the same settings as the default version minus linking exporter features.

The UI settings of a product are defined by implementing a ```create_config()``` function, found in the referenced source code file (e.g. ```config_product_new.cpp```).
The menus are filled using the IDs used to define certain features.

```
#include "config.h"
#include "config_standard.h"

namespace core
{
void create_config(Config& c)
{
    fill_app_menu(c);

    generic_menu_element menu;
    menu.name = "Menu";
    add_to_menu(CommandID{"cmd.fill.grey"}, "Fill Grey", menu);
    c.generic_menus.push_back(menu);

    c.width  = 512;
    c.height = 512;
}
}
```

## UI

The UI for all UI-based products is implemented as a separate library.
The UI elements are created based on the configuration defined in above ```create_config()``` function.
