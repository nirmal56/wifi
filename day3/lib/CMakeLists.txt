cmake_minimum_required(VERSION 3.7.2)
project(networkStatus)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#   set(THIRD_PARTY_POSTFIX d)
# endif()

set(MY_BASE ${PROJECT_SOURCE_DIR})
set(MY_THIRD_PARTY ${PROJECT_SOURCE_DIR}/src)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GLIB REQUIRED glib-2.0)
# find_package(NetworkManager 0.7.0)
# pkg_check_modules( NETWORKMANAGER libnm )
# pkg_check_modules(NetworkManager NetworkManager)
# pkg_search_module(libnmUtils libnm-util)
# MARK_AS_ADVANCED(NETWORKMANAGER_INCLUDE_DIRS)

# pkg_check_modules(libnm REQUIRED libnm)
include_directories(
	src/include/
	${GLIB_INCLUDE_DIRS}
)

file(GLOB SRC src/*.c)
# include_directories(${MY_THIRD_PARTY}/glib-2.0)
include_directories(${MY_THIRD_PARTY}/libnm)

link_directories(${MY_THIRD_PARTY}/pkgconfig)
link_directories(${MY_THIRD_PARTY}/libnm)
# find_package(lglib-2.0)
# find_package(libnm)

include_directories(${MY_THIRD_PARTY})
# 
# link_directories(${PROJECT_SOURCE_DIR}/src/*)



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

target_link_libraries(networkStatus PUBLIC ${mylib})


# target_include_directories(networkStatus PRIVATE ${GLIB_INCLUDE_DIRS})
# target_link_libraries(networkStatus INTERFACE ${GLIB_LDFLAGS})