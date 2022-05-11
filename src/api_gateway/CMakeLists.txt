cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME "api_gateway")

add_executable(${TARGET_NAME}
  main.cpp
  src/api_gateway_handler.cpp
  src/details_adapter.cpp
  src/api_gateway_router.cpp
  src/workers_adapter.cpp
)

target_include_directories(${TARGET_NAME} PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/inc/
                           )

target_link_libraries(${TARGET_NAME} net_lib)
