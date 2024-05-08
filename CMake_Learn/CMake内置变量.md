总结一下，这是一些常见的CMake变量：

- `CMAKE_SOURCE_DIR`: 顶级 CMakeLists.txt 所在的源代码目录的路径。
- `CMAKE_BINARY_DIR`: 执行 CMake 构建命令的目标目录的路径。
- `CMAKE_CURRENT_SOURCE_DIR`: 当前处理的 CMakeLists.txt 所在的源代码目录的路径。
- `CMAKE_CURRENT_BINARY_DIR`: 当前处理的 CMakeLists.txt 所在的目标目录的路径。
- `CMAKE_CURRENT_LIST_DIR`: 当前处理的 CMakeLists.txt 的完整路径，包括文件名。
- `CMAKE_MODULE_PATH`: 用于指定查找 CMake 模块文件的路径。
- `CMAKE_PREFIX_PATH`: 用于指定安装前缀的路径，用于搜索第三方库和工具。
- `CMAKE_C_COMPILER`: C编译器的路径。
- `CMAKE_CXX_COMPILER`: C++编译器的路径。
- `CMAKE_BUILD_TYPE`: 指定构建类型，例如Debug或Release。
- `CMAKE_INSTALL_PREFIX`: 指定安装目录的路径。
- `CMAKE_LIBRARY_OUTPUT_DIRECTORY`: 指定库文件输出的路径。
- `CMAKE_RUNTIME_OUTPUT_DIRECTORY`: 指定可执行文件输出的路径。
- `CMAKE_INCLUDE_PATH`: 指定额外的头文件搜索路径。
- `CMAKE_LIBRARY_PATH`: 指定额外的库文件搜索路径。
- `CMAKE_SYSTEM_NAME`: 指定目标系统的名称，例如Linux或Windows。
- `CMAKE_SYSTEM_VERSION`: 指定目标系统的版本号。
- `CMAKE_SYSTEM_PROCESSOR`: 指定目标系统的处理器架构。
- `CMAKE_VERSION`: CMake的版本号。
- `CMAKE_PROJECT_NAME`: 当前项目的名称。
- `CMAKE_CURRENT_LIST_FILE`: 当前处理的CMakeLists.txt文件的完整路径和文件名。
- `CMAKE_CURRENT_LIST_LINE`: 当前处理的CMakeLists.txt文件中的行号。
- `CMAKE_COMMAND`: 用于执行CMake命令的完整路径和文件名。
- `CMAKE_CONFIGURATION_TYPES`: 可用的构建类型列表。
- `CMAKE_SYSTEM`: 目标系统的名称和版本号的组合。
- `CMAKE_SYSTEM_INFO_FILE`: 用于存储目标系统信息的缓存文件路径。
- `CMAKE_SIZEOF_VOID_P`: 指针的大小（以字节为单位）。

这些变量可以帮助您在CMake脚本中获取有关项目、构建环境和目标系统的信息，以便于自定义和管理项目。
set(myVariable "Hello")
message("The value of myVariable is: ${myVariable}")
message("The value of myVariable is: " myVariable)