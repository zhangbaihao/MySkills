#add_subdirectory(cpp-examples)
cmake_minimum_required(VERSION 3.5)
project(open3d-examples)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DCURL_STATICLIB)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/open3d/3rdparty)

file(GLOB M_HEADER ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB M_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
aux_source_directory(${PROJECT_SOURCE_DIR}/src M_SOURCES)

link_directories(${PROJECT_SOURCE_DIR}/lib)
#执行程序生成路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
#使用vcpkg
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Windows 系统
    # 在这里添加针对 Windows 的设置和配置
    # 设置编译选项，包含调试符号并禁用优化
    message(STATUS "CMAKE_SYSTEM_NAME : ${CMAKE_SYSTEM_NAME}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG:FULL /OPT:REF /OPT:ICF")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG:FULL /OPT:REF /OPT:ICF")
    #无控制台
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Linux 系统
    # 在这里添加针对 Linux 的设置和配置
    # 设置编译选项，包含调试符号并禁用优化
    set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -g -O2 -Wall")
else()
    # 其他系统
    # 在这里添加针对其他系统的设置和配置
endif()

add_executable(${PROJECT_NAME} ${M_HEADER}${M_SOURCES})

#链接库
target_link_libraries(${PROJECT_NAME} Open3D.lib)