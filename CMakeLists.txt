cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(architecture)

enable_testing()

include(cmake/qt.cmake)
include(cmake/gtest.cmake)
include(cmake/modules.cmake)
include(cmake/utility.cmake)


set(PRODUCT_VERSION "1.0.1")
include(cmake/products/product.cmake)
include(cmake/products/demo.cmake)
include(cmake/products/deluxe.cmake)
include(cmake/products/mini.cmake)
include(cmake/products/cmdl.cmake)
include(cmake/products/intern.cmake)

include(cmake/tests.cmake)

