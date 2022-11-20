add_library(lib_image OBJECT)
target_sources(lib_image PRIVATE src/image_impl/image.cpp)
target_include_directories(lib_image PUBLIC src/image)

add_library(lib_core OBJECT)
target_sources(lib_core PRIVATE 
        src/core_impl/commands.cpp
        src/core_impl/config.cpp
        src/core_impl/app_commands.cpp
        src/core_impl/labels.cpp
        src/core_impl/exports.cpp)
target_include_directories(lib_core PRIVATE src/core_impl)
target_include_directories(lib_core PUBLIC src/core)
target_include_directories(lib_core PRIVATE src/image)


add_library(lib_cmd_colors OBJECT)
target_sources(lib_cmd_colors PRIVATE 
            src/commands/colors.cpp
            src/commands/secondary_colors.cpp)
target_include_directories(lib_cmd_colors PRIVATE src/core)
target_include_directories(lib_cmd_colors PUBLIC src/image)


add_library(lib_cmd_filters OBJECT)
target_sources(lib_cmd_filters PRIVATE 
            src/commands/filters.cpp)
target_include_directories(lib_cmd_filters PRIVATE src/core)
target_include_directories(lib_cmd_filters PUBLIC src/image)


add_library(lib_cmd_random OBJECT)
target_sources(lib_cmd_random PRIVATE 
            src/commands/random.cpp)
target_include_directories(lib_cmd_random PRIVATE src/core)
target_include_directories(lib_cmd_random PUBLIC src/image)

add_library(lib_cmd_pattern OBJECT)
target_sources(lib_cmd_pattern PRIVATE 
            src/commands/pattern.cpp)
target_include_directories(lib_cmd_pattern PRIVATE src/core)
target_include_directories(lib_cmd_pattern PUBLIC src/image)

add_library(lib_cmd_dev OBJECT)
target_sources(lib_cmd_dev PRIVATE 
            src/commands/dev.cpp)
target_include_directories(lib_cmd_dev PRIVATE src/core)
target_include_directories(lib_cmd_dev PUBLIC src/image)



add_library(lib_qt_image_utils OBJECT)
target_include_directories(lib_qt_image_utils PUBLIC src/qt_util)
target_sources(lib_qt_image_utils PRIVATE 
    src/qt_util/image_util.cpp )
target_link_libraries(lib_qt_image_utils PRIVATE Qt5::Widgets)
target_include_directories(lib_qt_image_utils PRIVATE src/core)
target_include_directories(lib_qt_image_utils PRIVATE src/image)

set(CMAKE_AUTOMOC ON)

add_library(lib_ui_app OBJECT)
target_sources(lib_ui_app PRIVATE 
    src/ui/ui_app.cpp 
    src/ui/main_window.cpp 
    src/ui/main_window.h
    src/ui/utility.h
    src/ui/utility.cpp
    src/ui/display.cpp
    src/ui/display.h
    src/ui/ui_modules.cpp
    src/ui/ui_module_macros.cpp
    src/ui/ui_module_commands.cpp
    src/ui/ui_module_app_commands.cpp
    src/ui/ui_module_exports.cpp)
target_include_directories(lib_ui_app PRIVATE src/core)
target_include_directories(lib_ui_app PRIVATE src/image)
target_include_directories(lib_ui_app PRIVATE src/apps)
target_link_libraries(lib_ui_app PRIVATE Qt5::Widgets)
target_link_libraries(lib_ui_app PRIVATE lib_qt_image_utils)

set(CMAKE_AUTOMOC OFF)



add_library(lib_exports OBJECT)
target_sources(lib_exports PRIVATE 
    src/export/export_png.cpp)
target_include_directories(lib_exports PRIVATE src/core)
target_include_directories(lib_exports PRIVATE src/image)
target_link_libraries(lib_exports PRIVATE Qt5::Widgets)
target_link_libraries(lib_exports PRIVATE lib_qt_image_utils)
