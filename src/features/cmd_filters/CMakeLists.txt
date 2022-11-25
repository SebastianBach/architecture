add_library(lib_cmd_filters OBJECT)
target_sources(lib_cmd_filters PRIVATE 
            filters.cpp)
target_link_libraries(lib_cmd_filters lib_core lib_image)
