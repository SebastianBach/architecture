add_library(lib_cmd_dev OBJECT)
target_sources(lib_cmd_dev PRIVATE 
            dev.cpp)
target_link_libraries(lib_cmd_dev lib_core lib_image)
