cmake_minimum_required(VERSION 3.1)

set(TARGET_NAME "oatpp-async-test")

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_executable(${TARGET_NAME}
        src/AppComponent.hpp
        src/App.cpp
        src/controller/MyController.hpp
        src/dto/DTOs.hpp
        src/Utils.cpp
        src/Utils.hpp
)

## link libs

find_package(oatpp  1.1.0 REQUIRED)
# find_package(mimalloc 1.0 REQUIRED)

target_link_libraries(${TARGET_NAME}
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-test
#        PUBLIC mimalloc-static
)

set_target_properties(${project_name} PROPERTIES
        CXX_STANDARD 11
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
        LINKER_LANGUAGE CXX
)

