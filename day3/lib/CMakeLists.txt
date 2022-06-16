cmake_minimum_required(VERSION 3.7.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(THIRD_PARTY_POSTFIX d)
endif()

set(MY_BASE ${PROJECT_SOURCE_DIR})
set(MY_THIRD_PARTY ${PROJECT_SOURCE_DIR}/src)

include_directories(${MY_THIRD_PARTY}/glib-2.0)
include_directories(${MY_THIRD_PARTY}/libnm)

link_directories(${MY_THIRD_PARTY}/glib-2.0)
link_directories(${MY_THIRD_PARTY}/libnm)


include_directories(${MY_THIRD_PARTY})
# 
# link_directories(${PROJECT_SOURCE_DIR}/src/*)

project(networkStatus)


set(mylib
    glib-2.0${THIRD_PARTY_POSTFIX}
    libnm${THIRD_PARTY_POSTFIX}
)


# add_library(mylib SHARED
#             checkstatus.h
#             checkstatus.cpp)
# file(GLOB SOURCES
#     "src/checkstatus.h"
#     "src/checkstatus.cpp"
# )
# 
# find_package(GLib2 REQUIRED)
# find_package(PkgConfig REQUIRED)
# # pkg_search_module(GLIB REQUIRED glib-2.0)

add_executable(networkStatus main.cpp)

target_link_libraries(networkStatus PUBLIC mylib)


# target_include_directories(networkStatus PRIVATE ${GLIB_INCLUDE_DIRS})
# target_link_libraries(networkStatus INTERFACE ${GLIB_LDFLAGS})