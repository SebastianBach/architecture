add_library(lib_cmd_pattern OBJECT)
target_sources(lib_cmd_pattern PRIVATE pattern.cpp)
target_link_libraries(lib_cmd_pattern PRIVATE lib_core lib_image)
