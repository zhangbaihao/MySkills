# CMake 使用语言家翻译功能

# 1.CMake添加以下代码
#  查找Qt翻译工具
find_package(Qt6 COMPONENTS LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS LinguistTools REQUIRED)
#  初始化要使用的列表
set(TS_FILES)
set(QM_FILES)

#  将要生成的翻译文件添加到列表中
list(APPEND TS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/qrc/english.ts)
list(APPEND TS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/qrc/chinese.ts)
#  设置翻译文件的生成路径，如果不指定就会生成在CMakeFiles的目录里
set_source_files_properties(${TS_FILES} PROPERTIES OUTPUT_LOCATION ${PROJECT_SOURCE_DIR}/qrc)

#  创建翻译的最关键一步
qt6_create_translation(QM_FILES ${TS_FILES} ${M_SOURCES})

message("-----------------------------------------------------")
message(${QM_FILES})
message(${PROJECT_SOURCE_DIR})

# 添加更新翻译的目标
add_custom_target(lupdate_task DEPENDS ${TS_FILES})
add_custom_target(lrelease_task DEPENDS ${QM_FILES})

# 2.生成的english.ts文件在qrc目录，打开填入对应翻译英文

# 3.在qrc文件添加资源
<file>chinese.qm</file>
<file>english.qm</file>

# 4.使用代码 translator 声明周期要直到程序结束
QTranslator translator;
int m_language = Config("Function").Get("Para", "m_Language").toInt();
if (m_language == 0)
{
    translator.load(":/chinese.qm");
    a.installTranslator(&translator);
}
else
{
    translator.load(":/english.qm");
    a.installTranslator(&translator);
}