set(TARGET_NAME details_unit_tests)
set(CMAKE_CXX_STANDARD 17)

file(GLOB src "./src/*.cpp" "./inc/*.h")
set(TEST_SRC
  ${PROJECT_SOURCE_DIR}/details/src/producer.cpp
  ${PROJECT_SOURCE_DIR}/details/src/detail.cpp
  ${PROJECT_SOURCE_DIR}/details/src/postgres_details_repository.cpp
  ${PROJECT_SOURCE_DIR}/details/src/details_facade.cpp
  ${PROJECT_SOURCE_DIR}/details/src/swaps_controller.cpp
    )

add_executable(${TARGET_NAME} ${src} ${TEST_SRC})

target_include_directories(${TARGET_NAME}
                           PUBLIC
                           ${PROJ_INC_DIRS}
                           ${PROJECT_SOURCE_DIR}/details/inc
                           ${PROJECT_SOURCE_DIR}/net_lib/exceptions
                           ${CMAKE_CURRENT_SOURCE_DIR}/inc
                           )

target_link_libraries(${TARGET_NAME} PRIVATE net_lib jsoncpp_lib gmock GTest::GTest GTest::Main pq
    pqxx)

file(INSTALL ./conf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME cg_course_tests COMMAND ${TARGET_NAME})
