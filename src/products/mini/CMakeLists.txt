add_executable(app_product_mini)
make_generic_app("The Product - Mini Edition" ${PRODUCT_VERSION} "product_mini" config_mini.cpp app_product_mini)
use_qt_ui(app_product_mini)
target_link_libraries(app_product_mini PRIVATE lib_cmd_colors)
target_link_libraries(app_product_mini PRIVATE lib_exports)

add_test(test_product_mini "product_mini" "test")
