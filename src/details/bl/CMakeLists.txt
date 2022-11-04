cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME "details_bl")

add_library(${TARGET_NAME}
  src/producer.cpp
  src/detail.cpp
  src/stock_log.cpp
  src/details_facade.cpp
  src/swaps_controller.cpp
)

target_include_directories(${TARGET_NAME} PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/inc/
                           )

target_link_libraries(${TARGET_NAME}
    net_lib
    jsoncpp_lib)
