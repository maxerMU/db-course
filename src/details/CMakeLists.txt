cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME "details")

add_executable(${TARGET_NAME}
  main.cpp
)

# target_include_directories(${TARGET_NAME} PUBLIC
#                            ${CMAKE_CURRENT_SOURCE_DIR}/inc/
#                            )

add_subdirectory(bl)
add_subdirectory(da)

target_link_libraries(${TARGET_NAME}
    net_lib
    jsoncpp_lib
    pq
    pqxx
    details_bl
    details_da
    )

# add_subdirectory(unit_tests)
