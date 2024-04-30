cmake_minimum_required(VERSION 3.5)

project(QtModule VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Network Multimedia MultimediaWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network Multimedia MultimediaWidgets)

# 设置 OpenCV 的路径
set(OpenCV_DIR "E:\\opencv4.9\\opencv\\build\\x64\\vc16\\lib")
find_package(OpenCV REQUIRED COMPONENTS opencv_world)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}) 
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include) 

add_compile_options(/Zi /Od /RTC1)
add_link_options(/DEBUG)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

FILE(GLOB M_UI ${PROJECT_SOURCE_DIR}/ui/*.ui)
FILE(GLOB M_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
FILE(GLOB M_HEADER ${PROJECT_SOURCE_DIR}/include/*.h)

add_executable(${PROJECT_NAME} ${M_HEADER} ${M_SOURCES} ${M_UI})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt::Network Qt::Multimedia Qt::MultimediaWidgets ${OpenCV_LIBS})


#使用UIC处理.ui文件
Qt6_WRAP_UI(${M_UI}_HEADER ${M_UI})

#调用预编译器MOC
Qt6_WRAP_CPP(${M_SOURCES}_MOC ${M_SOURCES})
