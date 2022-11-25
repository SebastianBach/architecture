cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(architecture)

enable_testing()

include(cmake/qt.cmake)
include(cmake/gtest.cmake)
include(cmake/utility.cmake)

set(PRODUCT_VERSION "1.0.1")
add_subdirectory(src)

set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)
set_target_properties(app_product_cmdl PROPERTIES FOLDER "products")
set_target_properties(app_product PROPERTIES FOLDER "products")
set_target_properties(app_product_demo PROPERTIES FOLDER "products")
set_target_properties(app_product_deluxe PROPERTIES FOLDER "products")
set_target_properties(app_product_mini PROPERTIES FOLDER "products")
set_target_properties(app_intern_dev PROPERTIES FOLDER "products")

set_target_properties(lib_core PROPERTIES FOLDER "core + utility")
set_target_properties(lib_image PROPERTIES FOLDER "core + utility")
set_target_properties(lib_qt_image_utils PROPERTIES FOLDER "core + utility")

set_target_properties(lib_cmd_colors PROPERTIES FOLDER "features")
set_target_properties(lib_cmd_dev PROPERTIES FOLDER "features")
set_target_properties(lib_cmd_filters PROPERTIES FOLDER "features")
set_target_properties(lib_cmd_pattern PROPERTIES FOLDER "features")
set_target_properties(lib_cmd_random PROPERTIES FOLDER "features")
set_target_properties(lib_exports PROPERTIES FOLDER "features")

set_target_properties(lib_ui_app PROPERTIES FOLDER "ui")

set_target_properties(unit_tests_basics PROPERTIES FOLDER "unit tests")
