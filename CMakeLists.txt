cmake_minimum_required (VERSION 3.1)

# Cross-build
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_C_COMPILER /usr/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabihf-g++)
set(CMAKE_PREFIX_PATH /usr/arm-linux-gnueabihf)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Set up project
set(PROJECT_NAME ski-tracker)
project(${PROJECT_NAME})
set(EXECUTABLE_NAME ${PROJECT_NAME})

if (NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Release)
endif()

# Build definitions
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Werror -O2")

# Dependencies
if (NOT DEFINED CMAKE_FIND_ROOT_PATH)
   message(FATAL_ERROR
	 "CMAKE_FIND_ROOT_PATH not set. Please set it to a location containing ARM libs for cross-compilation."
   )
endif()

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.71.0 REQUIRED system)
find_package(Threads)

if (NOT Boost_FOUND)
   message(SEND_ERROR "Could not find suitable version of Boost")
   set(ERROR_MISSING_DEP TRUE)
endif()

if (ERROR_MISSING_DEP)
   message(FATAL_ERROR "One or more required packages not found.")
endif()

include_directories(
  deps/cppnmea/include
  ${Boost_INCLUDE_DIRS}
)

# Project sources
add_subdirectory(src)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
