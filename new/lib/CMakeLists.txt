cmake_minimum_required(VERSION 3.7.2)
project(nicStatus)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# rapidjson header include
# find_package(rapidjson REQUIRED
# include(${CMAKE_SOURCE_DIR}/vendor/rapidjson.cmake)

add_executable(nicStatus main.cpp rtnetlink.cpp rtnetlink.h)


