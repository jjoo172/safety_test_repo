cmake_minimum_required(VERSION 3.16)
project(safety_test_repo CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

add_executable(app
    src/main.cpp
    src/config.cpp
    src/registry.cpp
    src/scheduler.cpp
    src/stats.cpp
    src/wire.cpp
)
target_compile_options(app PRIVATE -Wall -Wextra)
target_link_libraries(app PRIVATE Threads::Threads)
