cmake_minimum_required(VERSION 3.20)
project(dBStudioReaperCore VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(dbstudio_core
    src/channel_router/channel_router.cpp
)
target_include_directories(dbstudio_core PUBLIC include)
if(MSVC)
    target_compile_options(dbstudio_core PRIVATE /W4 /permissive-)
else()
    target_compile_options(dbstudio_core PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

include(CTest)
if(BUILD_TESTING)
    add_executable(dbstudio_core_tests tests/unit/channel_router_tests.cpp)
    target_link_libraries(dbstudio_core_tests PRIVATE dbstudio_core)
    add_test(NAME dbstudio_core_tests COMMAND dbstudio_core_tests)
endif()
