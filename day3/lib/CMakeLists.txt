cmake_minimum_required(VERSION 3.7.2)
project(networkStatus)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(MY_BASE ${PROJECT_SOURCE_DIR})
set(MY_THIRD_PARTY ${PROJECT_SOURCE_DIR}/src)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0 gio-2.0)
pkg_check_modules(LIBNM REQUIRED libnm)

include_directories(
    src/
    ${GLIB_INCLUDE_DIRS}
    ${LIBNM_INCLUDE_DIRS}
)

set(mylib
    glib-2.0
    nm
    ${GLIB_LIBRARIES}
)

add_executable(networkStatus main.cpp checkstatus.cpp checkstatus.h)

# target_link_directories(networkStatus PUBLIC ${MY_THIRD_PARTY})
find_library(LIBNMLIB protobuf HINTS /usr/include/libnm)

target_link_libraries(networkStatus ${mylib})

# include_directories(${MY_THIRD_PARTY}/glib-2.0)
# include_directories(${MY_THIRD_PARTY}/libnm)
# include_directories(${MY_THIRD_PARTY})
# include_directories($)
# link_directories(${MY_THIRD_PARTY}/libnm)

# some other methods that didn't work here but might work when dependencies like pkgconfig is not in between

# file(GLOB SRC src/*.c)
# if(CMAKE_BUILD_TYPE STREQUAL "Debug")
# set(THIRD_PARTY_POSTFIX d)
# endif()
# find_package(NetworkManager 0.7.0)
# pkg_check_modules( NETWORKMANAGER libnm )
# pkg_check_modules(NetworkManager NetworkManager)
# pkg_search_module(libnmUtils libnm-util)
# MARK_AS_ADVANCED(NETWORKMANAGER_INCLUDE_DIRS)

# pkg_check_modules(libnm REQUIRED libnm)
# link_directories(${MY_THIRD_PARTY}/pkgconfig)

# find_package(lglib-2.0)
# find_package(libnm)
# link_directories(${PROJECT_SOURCE_DIR}/src/*)
# add_library(mylib SHARED
# checkstatus.h
# checkstatus.cpp)
# file(GLOB SOURCES
# "src/checkstatus.h"
# "src/checkstatus.cpp"
# )
#
# find_package(GLib2 REQUIRED)
# find_package(PkgConfig REQUIRED)
# pkg_search_module(GLIB REQUIRED glib-2.0)

# target_include_directories(networkStatus PRIVATE ${GLIB_INCLUDE_DIRS})
# target_link_libraries(networkStatus INTERFACE ${GLIB_LDFLAGS})