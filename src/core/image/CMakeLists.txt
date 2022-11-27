add_library(lib_image OBJECT)
target_sources(lib_image PRIVATE image.cpp)
target_include_directories(lib_image PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(MSVC)
    target_compile_options(lib_image PRIVATE /W4 /WX)
endif()
