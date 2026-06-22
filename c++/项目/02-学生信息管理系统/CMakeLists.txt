# ==================== 学生信息管理系统 — CMake 构建配置 ====================
# 这是一个多文件 C++ 项目，综合运用了：
#   - STL 容器 (vector, map, set)
#   - 智能指针 (unique_ptr)
#   - 模板 (Repository<T>)
#   - 多态 (Person → Student/Teacher)
#   - Lambda + 算法
#   - 异常处理
#   - 文件 I/O (CSV 持久化)

cmake_minimum_required(VERSION 3.14)
project(StudentManagement VERSION 1.0.0 LANGUAGES CXX)

# C++17 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 收集所有源文件
set(SOURCES
    main.cpp
    src/Person.cpp
    src/Student.cpp
    src/Teacher.cpp
    src/FileManager.cpp
    src/Utils.cpp
)

# 可执行文件
add_executable(student_mgr ${SOURCES})

# 头文件路径
target_include_directories(student_mgr PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 编译警告
if(MSVC)
    target_compile_options(student_mgr PRIVATE /W4 /utf-8)
else()
    target_compile_options(student_mgr PRIVATE -Wall -Wextra)
endif()

# 链接 filesystem 库 (某些 GCC 版本需要)
if(CMAKE_COMPILER_IS_GNUCXX AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
    target_link_libraries(student_mgr PRIVATE stdc++fs)
endif()

message(STATUS "学生信息管理系统 — 构建配置完成")
message(STATUS "  构建: mkdir build && cd build && cmake .. && cmake --build .")
