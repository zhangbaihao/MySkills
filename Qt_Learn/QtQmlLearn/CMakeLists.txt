cmake_minimum_required(VERSION 3.5)
project(QtQmlLearn LANGUAGES CXX)
# project()命令之后包含Options.cmake文件
#include(cmake/Options.cmake)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#自动搜索cpp文件所在目录下头文件
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

#添加宏定义 utf8支持
ADD_DEFINITIONS(-DUNICODE -D_UNICODE)

#查找Qt6库
find_package(Qt6 COMPONENTS Core Widgets Quick Qml QuickWidgets REQUIRED)

# 设置头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/3rdparty/include)

#执行程序生成路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

message(STATUS "SOURCES : ${SOURCES}")
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")
message(STATUS "Source Directory: ${PROJECT_SOURCE_DIR}")
message(STATUS "QT_VERSION_MAJOR : ${QT_VERSION_MAJOR}")

#查找当前文件夹中的所有源代码文件，也可以通过Set命令将所有文件设置为一个变量
FILE(GLOB M_HEADER ${PROJECT_SOURCE_DIR}/include/*.h)
FILE(GLOB M_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
FILE(GLOB M_UI ${PROJECT_SOURCE_DIR}/ui/*.ui)
FILE(GLOB M_QRC ${PROJECT_SOURCE_DIR}/qrc/*.qrc)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/src M_SOURCES)

qt_add_executable(${PROJECT_NAME} qml.qrc ${M_HEADER} ${M_SOURCES})
#添加调试信息
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

#链接库
#target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
#target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Quick Qt6::Qml Qt6::Widgets Qt6::QuickWidgets)
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
