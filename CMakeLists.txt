cmake_minimum_required(VERSION 3.24)

### Setting up vcpkg
# The vcpkg section needs to be before 'project command'
set(VCPKG_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg" CACHE STRING "Path to vcpkg")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_LOCATION}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Path to cmake toolchain file from vcpkg.")
set(VCPKG_TARGET_TRIPLET "x64-linux-release" CACHE STRING "Vcpkg target triplet")
set(VCPKG_LIBRARY_LINKAGE "static" CACHE STRING "Specifies the preferred library linkage.")

project(NA60+ LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_VERBOSE_MAKEFILE ON)

### Setting up the compiler
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

set(Boost_NO_WARN_NEW_VERSIONS ON)

set(PROJECT_GEANT4_USE_GUI OFF CACHE BOOL "Build the project with Geant4's GUI support.")


add_subdirectory(common)

add_subdirectory(src)
