add_executable(app_product_deluxe)
make_generic_app("The Product - Deluxe Edition" ${PRODUCT_VERSION} "product_deluxe" config_deluxe.cpp app_product_deluxe)
use_qt_ui(app_product_deluxe)
target_link_libraries(app_product_deluxe PRIVATE lib_cmd_colors)
target_link_libraries(app_product_deluxe PRIVATE lib_cmd_filters)
target_link_libraries(app_product_deluxe PRIVATE lib_cmd_random)
target_link_libraries(app_product_deluxe PRIVATE lib_cmd_pattern)
target_link_libraries(app_product_deluxe PRIVATE lib_exports)

add_test(test_product_deluxe "product_deluxe" "test")
