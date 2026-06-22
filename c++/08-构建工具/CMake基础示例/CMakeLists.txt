# ==================== CMake 基础示例 ====================
# CMake = 跨平台构建系统生成器
#   它不直接编译代码，而是生成 Makefile / Visual Studio 项目 / ninja 等
#
# CMake 工作流程:
#   1. 编写 CMakeLists.txt
#   2. mkdir build && cd build
#   3. cmake ..           (生成构建文件)
#   4. cmake --build .    (编译)
#   5. ./myapp            (运行)
#
# 现代 CMake 推荐风格:
#   - target_xxx() 代替全局设置
#   - 使用 PRIVATE / PUBLIC / INTERFACE 明确依赖范围
#   - 每个 CMakeLists.txt 有明确职责


# ---- 1. cmake_minimum_required: 指定最低 CMake 版本 ----
# 必须在第一行！版本号根据你使用的特性确定
cmake_minimum_required(VERSION 3.14)

# ---- 2. project: 定义项目 ----
# 同时设置项目名、版本、语言
project(CMakeDemo VERSION 1.0.0 LANGUAGES CXX)

# ---- 3. set: 设置变量 ----
# C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)      # 强制要求，不支持则报错
set(CMAKE_CXX_EXTENSIONS OFF)            # 禁用编译器扩展（增强可移植性）

# 自定义变量
set(MY_PROJECT_VERSION_MAJOR 1)
set(MY_PROJECT_VERSION_MINOR 0)


# ---- 4. add_executable: 创建可执行文件 ----
# 语法: add_executable(目标名 源文件...)
add_executable(cmake_demo
    main.cpp
    src/utils.cpp
)


# ---- 5. target_include_directories: 添加头文件搜索路径 ----
# PRIVATE:  只对当前目标的编译有效（不传播给依赖者）
# PUBLIC:   对当前目标和依赖此目标的其他目标都有效
# INTERFACE: 只对依赖此目标的其他目标有效（不用于自身编译）
target_include_directories(cmake_demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


# ---- 6. target_compile_options: 编译选项 ----
# 根据编译器设置不同的警告选项
if(MSVC)
    # Visual Studio 编译器选项
    target_compile_options(cmake_demo PRIVATE /W4)
else()
    # GCC / Clang 编译器选项
    target_compile_options(cmake_demo PRIVATE -Wall -Wextra -Wpedantic)
endif()


# ---- 7. 子目录 (多模块项目) ----
# 如果有子目录的 CMakeLists.txt:
# add_subdirectory(src)
# add_subdirectory(lib)


# ---- 8. 可选：生成配置头文件 ----
# configure_file 可以用 CMake 变量生成 C++ 头文件
# configure_file(config.h.in config.h)


# ---- 9. 调试信息 ----
message(STATUS "===== CMakeDemo 配置信息 =====")
message(STATUS "项目名:    ${PROJECT_NAME}")
message(STATUS "版本:      ${PROJECT_VERSION}")
message(STATUS "C++ 标准:  C++${CMAKE_CXX_STANDARD}")
message(STATUS "源文件目录: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "构建目录:   ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "编译器:     ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "==============================")


# ==================== 常用命令速查 ====================
#
# add_library(库名 STATIC/SHARED 源文件...)
#   - STATIC:  静态库 (.lib / .a)
#   - SHARED:  动态库 (.dll / .so)
#
# target_link_libraries(目标 PRIVATE/PUBLIC/INTERFACE 库名)
#   - 链接库到目标
#
# find_package(包名 REQUIRED)
#   - 查找外部库，如 find_package(OpenCV REQUIRED)
#
# add_subdirectory(子目录)
#   - 递归处理子目录中的 CMakeLists.txt
#
# option(变量 "描述" 默认值)
#   - 用户可配置的选项
#   - 例: option(ENABLE_TESTS "Build tests" ON)
#
# if/else/endif
#   - 条件判断
#   - if(CMAKE_BUILD_TYPE STREQUAL "Debug") ... endif()
