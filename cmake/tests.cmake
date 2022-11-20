
include(GoogleTest)

add_executable(unit_tests_basics 
    src/tests/test_error.cpp
    src/tests/test_empty.cpp
    src/tests/test_image.cpp
    src/tests/empty_config.cpp)
setup_unit_test(unit_tests_basics)
