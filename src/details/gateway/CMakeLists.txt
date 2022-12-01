cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME "details_gateway")

add_library(${TARGET_NAME}
  src/details_handler.cpp
  src/commands.cpp
  src/details_router.cpp
  src/converters.cpp
  src/detail_dto.cpp
  src/producer_data_dto.cpp
  src/swaps_part_name_dto.cpp
  src/detail_to_stock_dto.cpp
  src/get_stock_log_dto.cpp
)

target_include_directories(${TARGET_NAME} PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/inc/
                           ${CMAKE_CURRENT_SOURCE_DIR}/../bl/inc
                           )

target_link_libraries(${TARGET_NAME}
    details_bl
    net_lib
    jsoncpp_lib)
