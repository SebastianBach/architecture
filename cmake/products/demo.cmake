add_executable(app_product_demo)
make_generic_app("The Product - Demo Version" ${PRODUCT_VERSION} "product_demo" config_product.cpp app_product_demo)
use_qt_ui(app_product_demo)
target_link_libraries(app_product_demo PUBLIC lib_cmd_colors)
target_link_libraries(app_product_demo PUBLIC lib_cmd_filters)
target_link_libraries(app_product_demo PUBLIC lib_cmd_random)
target_link_libraries(app_product_demo PUBLIC lib_cmd_pattern)
# No exporters available
