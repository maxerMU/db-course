cmake_minimum_required(VERSION 3.12)


project(coroutine_server LANGUAGES CXX)


set(CMAKE_CXX_COMPILER g++-10)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines")

set(CMAKE_INCLUDE_PATH /usr/include/c++/10/)


find_package(Boost COMPONENTS system thread REQUIRED)
find_package(yaml-cpp)
find_package(jsoncpp CONFIG REQUIRED)
find_package(cpp-jwt REQUIRED)
find_package(GTest REQUIRED)
get_target_property(JSON_INC_PATH jsoncpp_lib INTERFACE_INCLUDE_DIRECTORIES)
include_directories(${JSON_INC_PATH})


add_subdirectory(net_lib)
add_subdirectory(api_gateway)
add_subdirectory(details)
add_subdirectory(workers)
# add_subdirectory(dummy_server)
# add_subdirectory(dummy_client_server)
