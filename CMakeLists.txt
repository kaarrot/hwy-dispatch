cmake_minimum_required(VERSION 3.15)

add_executable(aaa main.cpp dynamic_dispatch.cpp)

if (WIN32)
    set(HWY_INCLUDE C:/Users/kuba/SRC/highway)
    set(HWY_LIB_PATH C:/Users/kuba/SRC/highway/__build/RelWithDebInfo)
    set(HWY_LIB hwy.lib) # needs to be build with same optimization: RelWithDebInfo
else()
    set(HWY_INCLUDE /mnt/c/Users/kuba/SRC/highway/install_prefix_linux/include)
    set(HWY_LIB_PATH /mnt/c/Users/kuba/SRC/highway/install_prefix_linux/lib)
    set(HWY_LIB hwy.a)     
endif()

target_include_directories(aaa PRIVATE ${HWY_INCLUDE})
target_include_directories(aaa PRIVATE .) # recquired for HWY_TARGET_INCLUDE on Linux
target_link_directories(aaa PRIVATE ${HWY_LIB_PATH})
target_link_libraries(aaa PUBLIC ${HWY_LIB})

