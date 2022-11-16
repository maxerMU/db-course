cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME "benchmark_asio")

add_executable(${TARGET_NAME}
  main.cpp
  src/dummy_server_handler.cpp
)

target_include_directories(${TARGET_NAME} PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/inc/
                           )

target_link_libraries(${TARGET_NAME} net_lib)
