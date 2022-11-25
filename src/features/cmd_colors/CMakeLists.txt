add_library(lib_cmd_colors OBJECT)
target_sources(lib_cmd_colors PRIVATE 
            colors.cpp
            secondary_colors.cpp)
target_link_libraries(lib_cmd_colors lib_core lib_image)