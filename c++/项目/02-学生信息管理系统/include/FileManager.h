// FileManager.h — RAII 文件管理器
// 封装文件读写操作，异常安全 + 自动资源管理

#pragma once
#include<string>
#include<vector>
#include<memory>
#include<fstream>

class Person;  // 前向声明

class FileManager
{
public:
    // 保存到 CSV 文件
    // persons: 裸指针数组（不拥有所有权）
    static bool saveToCSV(const std::string& filename,
                          const std::vector<Person*>& persons);

    // 从 CSV 文件加载
    // 返回 unique_ptr 数组（所有权转移给调用者）
    static std::vector<std::unique_ptr<Person>>
        loadFromCSV(const std::string& filename);

private:
    // 从 CSV 的一行解析出 Person（工厂方法）
    static std::unique_ptr<Person> parseLine(const std::string& line);
};
