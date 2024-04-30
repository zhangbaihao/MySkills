# Options.cmake
option(USE_QT "Use Qt" OFF)
option(USE_VCPKG "Use vcpkg" OFF)
option(USE_OPENCV "Use opencv" OFF)

#cmake -DUSE_VCPKG=ON ..
if(USE_QT)
    set(CMAKE_PREFIX_PATH "C:/Qt/6.5.2/msvc2019_64" CACHE PATH "Qt installation path")
endif()

if(USE_VCPKG)
    set(CMAKE_TOOLCHAIN_FILE "F:/Code/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "vcpkg toolchain file")
    find_package(OpenCV REQUIRED)
else()
    if(USE_OPENCV) 
        #使用自己安装的opencv,而不是使用vcpkg安装的
        set(OpenCV_DIR "E:/opencv4.9/opencv/build/x64/vc16/lib")
        find_package(OpenCV REQUIRED COMPONENTS opencv_world)
        
    endif()
endif()

if(USE_VCPKG OR USE_OPENCV)
    if(NOT OpenCV_FOUND)
        message(FATAL_ERROR "OpenCV not found. Please install OpenCV or enable the appropriate option.")
    endif()
endif()
