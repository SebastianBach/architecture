add_library(lib_core OBJECT)
target_sources(lib_core PRIVATE 
        commands.cpp
        config.cpp
        app_commands.cpp
        labels.cpp
        exports.cpp)

target_include_directories(lib_core PUBLIC   ${CMAKE_CURRENT_SOURCE_DIR})
