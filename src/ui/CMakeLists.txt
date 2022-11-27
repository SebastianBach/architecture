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
    ui_module_generic_commands.cpp
    app.cpp
    app.h)

if(MSVC)
    target_compile_options(lib_ui_app PRIVATE /W4 /WX)
endif()

target_link_libraries(lib_ui_app PRIVATE Qt5::Widgets)
target_link_libraries(lib_ui_app PRIVATE lib_qt_image_utils lib_core lib_image lib_app_info)

set(CMAKE_AUTOMOC OFF)