function(setup_unit_test TARGET)

    target_link_libraries(${TARGET}
        GTest::gtest_main
        lib_image
        lib_core)

    gtest_discover_tests(${TARGET})

endfunction()


function(make_generic_app TargetName TargetVersion TargetBinary config_file TARGET)

    set_target_properties(${TARGET} PROPERTIES OUTPUT_NAME ${TargetBinary})

    set(APP_NAME ${TargetName}) 
    set(APP_VERSION ${TargetVersion})
    configure_file(${CMAKE_BINARY_DIR}/../src/app_info/app.cpp.in ${TARGET}_appname/app_info.cpp @ONLY)
    target_sources(${TARGET} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/${TARGET}_appname/app_info.cpp)

    target_sources(${TARGET} PRIVATE ${config_file})
    target_include_directories(${TARGET} PRIVATE src/config )

    target_link_libraries(${TARGET} PRIVATE lib_core)
    target_link_libraries(${TARGET} PRIVATE lib_image)
    target_link_libraries(${TARGET} PRIVATE lib_product_utils)

endfunction()


function(use_qt_ui TARGET)
    target_link_libraries(${TARGET} PRIVATE lib_ui_app)
    target_link_libraries(${TARGET} PRIVATE Qt5::Widgets)
    target_link_libraries(${TARGET} PRIVATE lib_qt_image_utils)
endfunction()
