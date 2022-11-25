add_library(lib_qt_image_utils OBJECT)
target_sources(lib_qt_image_utils PRIVATE image_util.cpp )
target_link_libraries(lib_qt_image_utils PRIVATE Qt5::Widgets lib_image)
target_include_directories(lib_qt_image_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
