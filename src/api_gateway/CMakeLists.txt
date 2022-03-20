cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME "api_gateway")

add_executable(${TARGET_NAME}
  main.cpp
  src/api_gateway_handler.cpp
  # base/beast_req.cpp
  # connections/server_connection.cpp
  # sessions/echo_session.cpp
  # sessions/http_session.cpp
  # coroutines_support/read_awaiter.cpp
  # coroutines_support/http_read_awaiter.cpp
  # coroutines_support/http_write_awaiter.cpp
  # coroutines_support/write_awaiter.cpp
)

target_include_directories(${TARGET_NAME} PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/inc/
                           # ${CMAKE_CURRENT_SOURCE_DIR}/net_headers/
                           # ${CMAKE_CURRENT_SOURCE_DIR}/sessions/
                           # ${CMAKE_CURRENT_SOURCE_DIR}/connections/
                           )

target_link_libraries(${TARGET_NAME} net_lib Boost::system Boost::thread)
