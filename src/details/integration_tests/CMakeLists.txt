set(TARGET_NAME details_integration_tests)
set(CMAKE_CXX_STANDARD 17)

file(GLOB src "./src/*.cpp" "./inc/*.h")

add_executable(${TARGET_NAME} ${src} ${TEST_SRC})

target_include_directories(${TARGET_NAME}
                           PUBLIC
                           ${PROJ_INC_DIRS}
                           ${PROJECT_SOURCE_DIR}/details/bl/inc
                           ${PROJECT_SOURCE_DIR}/details/da/inc
                           ${PROJECT_SOURCE_DIR}/details/tests_lib/inc
                           ${PROJECT_SOURCE_DIR}/net_lib/exceptions
                           ${CMAKE_CURRENT_SOURCE_DIR}/inc
                           )

target_link_libraries(${TARGET_NAME} PRIVATE
    net_lib
    details_bl
    details_da
    details_tests
    jsoncpp_lib
    gmock
    GTest::GTest
    GTest::Main
    pq
    pqxx)


file(INSTALL ./conf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME details_integration_tests COMMAND ${TARGET_NAME})
