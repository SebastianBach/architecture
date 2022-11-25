set(CMAKE_AUTOMOC ON)

add_library(lib_ui_app OBJECT)
target_sources(lib_ui_app PRIVATE 
    ui_app.cpp 
    main_window.cpp 
    main_window.h
    utility.h
    utility.cpp
    display.cpp
    display.h
    ui_modules.cpp
    ui_module_macros.cpp
    ui_module_app_commands.cpp
    ui_module_generic_commands.cpp)

target_link_libraries(lib_ui_app PRIVATE Qt5::Widgets)
target_link_libraries(lib_ui_app PRIVATE lib_qt_image_utils lib_core lib_image lib_app_info)

set(CMAKE_AUTOMOC OFF)