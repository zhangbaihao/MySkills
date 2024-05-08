# 项目名称
简要介绍项目是使用CMake构建的Qt 6.5.2程序，并在Visual Studio 2022中进行开发。

## 依赖项
- Qt 6.5.2：用于构建和运行Qt应用程序。
- Visual Studio 2022：用于开发和构建项目。
- CMakeLists和c_cpp_properties.json 查找的路径 C:\\Qt\\6.5.2\\msvc2019_64，请直接安装Qt到C盘


## 构建和开发环境

以下是构建和开发该项目所需的环境设置步骤：

1. 安装Qt 6.5.2：请根据Qt官方文档的指引，在您的系统上安装Qt 6.5.2版本。

2. 安装Visual Studio 2022：请根据Microsoft官方文档的指引，在您的系统上安装Visual Studio 2022。

3. 克隆项目：使用Git克隆该项目到本地：

## cmake文件夹 含有Qt opencv vcpkg 工具链以及库的设置使用方法 只需要 include(cmake/Options.cmake) 包含
1. 使用vcpkg 需要克隆下载 git clone https://github.com/microsoft/vcpkg.git
2. 设置vcpkg 环境变量
3. 安装64位windows系统opencv4 vcpkg install opencv4:x64-windows 或者 vcpkg install opencv4[world]:x64-windows
4. 集成到全局 vcpkg integrate install

