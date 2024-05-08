CMake是一个功能强大的构建工具，用于管理和构建跨平台的C++项目。以下是一些常用的CMake操作：

1. `cmake_minimum_required(VERSION x.x)`：指定所需的最低CMake版本。
2. `project(project_name)`：指定项目的名称。
3. `add_executable(target_name source_files)`：添加一个可执行文件目标。
4. `add_library(target_name source_files)`：添加一个库目标。
5. `target_link_libraries(target_name library_names)`：将一个或多个库链接到目标。
6. `set(variable_name value)`：设置一个变量的值。
7. `if(condition)` 和 `endif()`：执行条件判断，用于在不同的条件下执行特定的操作。
8. `include_directories(directory_path)`：添加一个目录到头文件搜索路径。
9. `link_directories(directory_path)`：添加一个目录到库文件搜索路径。
10. `install(TARGETS targets DESTINATION directory)`：安装目标文件到指定目录。
11. `find_package(package_name)`：搜索并加载指定的第三方包。

这些是一些常见的CMake操作，用于管理项目的构建、依赖、安装和其他自定义配置。具体使用取决于您的项目需求和配置。


当您在命令行中使用CMake时，可以按照以下格式输入CMake命令：
```
cmake [options] <path-to-source>
```

其中，`path-to-source`是指项目源代码根目录的路径。

以下是一些常见的CMake命令和选项：

- `-G "generator"`：指定生成器，例如`-G "Visual Studio 17 2022"`用于生成Visual Studio 2019的项目文件。
- `-DVAR=VALUE`：设置变量的值，例如`-DMY_VARIABLE=ON`用于设置`MY_VARIABLE`为`ON`。
- `-DCMAKE_BUILD_TYPE=type`：指定构建类型，例如`-DCMAKE_BUILD_TYPE=Debug`用于设置构建类型为Debug。
- `-DCMAKE_INSTALL_PREFIX=path`：指定安装目录的路径，例如`-DCMAKE_INSTALL_PREFIX=/usr/local`用于设置安装目录为`/usr/local`。
- `--build <dir>`：指定构建目录，例如`--build build`用于在名为`build`的目录中进行构建。
- `--target <target>`：指定构建的目标，例如`--target myexe`用于构建名为`myexe`的可执行文件。

这些命令和选项可以根据您的需求进行组合和使用。您可以在命令行中运行`cmake --help`来查看更多的命令和选项。
cmake -G "Visual Studio 17 2022" ..
cmake -DMY_VARIABLE=ON ..
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..
cmake --build build --target myexe