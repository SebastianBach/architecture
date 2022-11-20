add_executable(app_product)
make_generic_app("The Product" ${PRODUCT_VERSION} "product_standard" config_product.cpp app_product)
use_qt_ui(app_product)
target_link_libraries(app_product PUBLIC lib_cmd_colors)
target_link_libraries(app_product PUBLIC lib_cmd_filters)
target_link_libraries(app_product PUBLIC lib_cmd_random)
target_link_libraries(app_product PUBLIC lib_cmd_pattern)
target_link_libraries(app_product PRIVATE lib_exports)