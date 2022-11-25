add_library(lib_cmd_random OBJECT)
target_sources(lib_cmd_random PRIVATE random.cpp)
target_link_libraries(lib_cmd_random lib_core lib_image)
