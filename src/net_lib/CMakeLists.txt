cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME "net_lib")

add_library(${TARGET_NAME}
  base/beast_req.cpp
  base/beast_resp.cpp
  connections/server_connection.cpp
  connections/client_server_connection.cpp
  sessions/echo_session.cpp
  sessions/http_session.cpp
  sessions/http_client_server_session.cpp
  coroutines_support/read_awaiter.cpp
  coroutines_support/http_read_awaiter.cpp
  coroutines_support/http_write_awaiter.cpp
  coroutines_support/write_awaiter.cpp
  crypto/sha256_encrypt.cpp
  crypto/jwt_token_generator.cpp
  config/yamlcpp_config.cpp
)

target_include_directories(${TARGET_NAME} PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/base/
                           ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/
                           ${CMAKE_CURRENT_SOURCE_DIR}/coroutines_support/
                           ${CMAKE_CURRENT_SOURCE_DIR}/net_headers/
                           ${CMAKE_CURRENT_SOURCE_DIR}/sessions/
                           ${CMAKE_CURRENT_SOURCE_DIR}/connections/
                           ${CMAKE_CURRENT_SOURCE_DIR}/config/
                           ${CMAKE_CURRENT_SOURCE_DIR}/crypto/
                           )

target_link_libraries(${TARGET_NAME} yaml-cpp Boost::system Boost::thread cpp-jwt::cpp-jwt)
