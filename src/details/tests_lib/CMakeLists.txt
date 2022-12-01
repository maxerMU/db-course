set(TARGET_NAME details_tests)
set(CMAKE_CXX_STANDARD 17)

file(GLOB src "./src/*.cpp" "./inc/*.h")

add_library(${TARGET_NAME} ${src} ${TEST_SRC})

target_include_directories(${TARGET_NAME}
                           PUBLIC
                           ${PROJ_INC_DIRS}
                           ${PROJECT_SOURCE_DIR}/details/bl/inc
                           ${PROJECT_SOURCE_DIR}/details/da/inc
                           ${PROJECT_SOURCE_DIR}/net_lib/exceptions
                           ${CMAKE_CURRENT_SOURCE_DIR}/inc
                           )

target_link_libraries(${TARGET_NAME} PRIVATE
    details_bl
    details_da
    jsoncpp_lib)
