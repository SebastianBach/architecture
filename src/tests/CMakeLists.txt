include(GoogleTest)

add_executable(unit_tests_basics 
    test_error.cpp
    test_empty.cpp
    test_image.cpp
    empty_config.cpp)
setup_unit_test(unit_tests_basics)
