# FileName: CMakeLists.txt
# Description: Configures, makes and installs ARMAMIN.
# Copyright (C) 2014  K M Masum Habib <masum.habib@gmail.com>
# Created on: Nov 02, 2014

cmake_minimum_required(VERSION 2.8)

# Version
set(ARMAMIN_MAJOR 0)
set(ARMAMIN_MINOR 00)
set(ARMAMIN_PATCH 1)

set(ARMAMIN_CXX_11 on)
set(CMAKE_VERBOSE_MAKEFILE      off)
#set(LINK_SEARCH_START_STATIC    on)
#set(CMAKE_BUILD_TYPE "Debug")


# Start configuration
set(ARMAMIN_VERSION ${ARMAMIN_MAJOR}.${ARMAMIN_MINOR}.${ARMAMIN_PATCH})
message(STATUS "Configuring ARMAMIN ${ARMAMIN_VERSION}")
message(STATUS "System: ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_PROCESSOR}")

project(armamin CXX)

# For custom cmake scripts
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


# Options
# -----------------------------------------------------------------------------
#Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" )
endif()

# Compiler flags
if (ARMAMIN_CXX_11)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()
# optimization
#set(CMAKE_CXX_FLAGS_RELEASE " -m64 -O2 -MMD -MP -MF ")

# Libraries
# -----------------------------------------------------------------------------
# Armadillo
find_package(Armadillo REQUIRED)

# Sources and headers
# -----------------------------------------------------------------------------
# Prepare distribution directory
set(ARMAMIN_DIST_DIR ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-${ARMAMIN_VERSION})
set(EXECUTABLE_OUTPUT_PATH ${ARMAMIN_DIST_DIR}/bin)

# version header
configure_file (
    "${CMAKE_SOURCE_DIR}/include/config.in.h"
    "${CMAKE_BINARY_DIR}/CMakeFiles/${PROJECT_NAME}.dir/include/config.h"
)

# includes
set(ARMAMIN_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include)
list(REMOVE_DUPLICATES ARMAMIN_INCLUDE_DIRS)
list(APPEND ARMAMIN_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/CMakeFiles/${PROJECT_NAME}.dir/include)

include_directories(${ARMAMIN_INCLUDE_DIRS})
include_directories(${ARMADILLO_INCLUDE_DIRS})

# -------- <ARMAMIN C++ Executable> ------------------------------------------------
# sources
file(GLOB_RECURSE ARMAMIN_SOURCES "src/*.cpp")
file(GLOB_RECURSE ARMAMIN_HEADERS "include/*.h*")
add_executable(armamin ${ARMAMIN_SOURCES} ${ARMAMIN_HEADERS})


# linking
target_link_libraries (armamin ${ARMADILLO_LIBRARIES})

# Prepare armamin package
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND cp -rp ${ARMAMIN_DIST_DIR}/bin/armamin ${CMAKE_SOURCE_DIR}/bin
)

# -------- </ARMAMIN C++ Executable> -----------------------------------------------

# installation
install(DIRECTORY ${ARMAMIN_DIST_DIR} DESTINATION .)

if(${CMAKE_BUILD_TYPE} MATCHES "Release")
    set(ARMAMIN_FLAGS ${CMAKE_CXX_FLAGS_RELEASE})
endif(${CMAKE_BUILD_TYPE} MATCHES "Release")

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(ARMAMIN_FLAGS ${CMAKE_CXX_FLAGS_DEBUG})
endif(${CMAKE_BUILD_TYPE} MATCHES "Debug")

message(STATUS "Compiler flags: ${ARMAMIN_FLAGS}")
message(STATUS "Linker flags: ${CMAKE_SHARED_LINKER_FLAGS}")

message(STATUS "Installation location: ${CMAKE_INSTALL_PREFIX}/${ARMAMIN_INSTALL_DIR}")

