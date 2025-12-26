# Standalone test for spdlog integration
cmake_minimum_required(VERSION 3.16.3)
project(SpdlogIntegrationTest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add spdlog
set(SPDLOG_BUILD_SHARED OFF CACHE BOOL "Build shared library" FORCE)
set(SPDLOG_BUILD_EXAMPLE OFF CACHE BOOL "Build example" FORCE)
set(SPDLOG_BUILD_TESTS OFF CACHE BOOL "Build tests" FORCE)
set(SPDLOG_INSTALL OFF CACHE BOOL "Generate the install target" FORCE)
add_subdirectory(../src/3rdParty/spdlog spdlog_build)

# Simple test executable
add_executable(test_spdlog_basic test_spdlog_basic.cpp)
target_include_directories(test_spdlog_basic PRIVATE 
    ../src/3rdParty/spdlog/include
)
target_link_libraries(test_spdlog_basic spdlog)

message(STATUS "Standalone spdlog test configured successfully")
