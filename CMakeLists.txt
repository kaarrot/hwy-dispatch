cmake_minimum_required(VERSION 3.15)
include(ExternalProject)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)


ExternalProject_Add(
  "hwy"
  PREFIX "external"
  GIT_REPOSITORY https://github.com/google/highway
  DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/hwy_download
  SOURCE_DIR ${CMAKE_BINARY_DIR}/hwy_src
  INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install_dir
  BUILD_COMMAND ""
  CMAKE_ARGS
  "-DCMAKE_BUILD_TYPE=RelWithDebInfo"
  "-DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/install_dir"
  "-DHWY_ENABLE_TESTS=0"
 )

 set(HWY_INCLUDE ${CMAKE_SOURCE_DIR}/install_dir/include)
 set(HWY_LIB_PATH ${CMAKE_SOURCE_DIR}/install_dir/lib)
if (WIN32)
    set(HWY_LIB hwy.lib) # needs to be build with same optimization: RelWithDebInfo
else()
    set(HWY_LIB hwy.a)     
endif()

add_executable(example main.cpp dynamic_dispatch.cpp)

# Build highway first
add_dependencies(example hwy)

target_include_directories(example PRIVATE ${HWY_INCLUDE})
target_include_directories(example PRIVATE .) # recquired for HWY_TARGET_INCLUDE on Linux
target_link_directories(example PRIVATE ${HWY_LIB_PATH})
target_link_libraries(example PUBLIC ${HWY_LIB})

