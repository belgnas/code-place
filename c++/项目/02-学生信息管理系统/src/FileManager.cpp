// FileManager.cpp — RAII 文件管理器实现

#include"FileManager.h"
#include"Person.h"
#include"Student.h"
#include"Teacher.h"
#include"Utils.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<stdexcept>
#include<memory>

bool FileManager::saveToCSV(const std::string& filename,
                            const std::vector<Person*>& persons)
{
    // ofstream 是 RAII 对象 — 构造时打开，析构时自动关闭
    std::ofstream fout(filename);
    if (!fout.is_open())
    {
        std::cerr << "[错误] 无法写入文件: " << filename << std::endl;
        return false;
    }

    // 写入标题行
    fout << "类型,ID,姓名,年龄,信息1,信息2" << std::endl;

    // 用范围 for + 多态写入每一条记录
    for (const auto* person : persons)
    {
        fout << person->toCSV() << std::endl;
    }

    std::cout << "[文件] 已保存 " << persons.size()
              << " 条记录到 " << filename << std::endl;
    return true;
}

std::vector<std::unique_ptr<Person>>
    FileManager::loadFromCSV(const std::string& filename)
{
    std::vector<std::unique_ptr<Person>> result;

    // ifstream 也是 RAII
    std::ifstream fin(filename);
    if (!fin.is_open())
    {
        std::cerr << "[警告] 文件不存在或无法打开: " << filename
                  << " (将使用空数据)" << std::endl;
        return result;
    }

    std::string line;
    int lineNum = 0;

    // 跳过标题行
    std::getline(fin, line);
    lineNum++;

    while (std::getline(fin, line))
    {
        lineNum++;
        if (line.empty()) continue;

        try
        {
            auto person = parseLine(line);
            if (person)
            {
                result.push_back(std::move(person));
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "[警告] 第 " << lineNum << " 行解析失败: "
                      << e.what() << std::endl;
        }
    }

    std::cout << "[文件] 从 " << filename << " 加载了 "
              << result.size() << " 条记录" << std::endl;
    return result;
}

std::unique_ptr<Person> FileManager::parseLine(const std::string& line)
{
    // 用 istringstream 解析 CSV 行
    auto fields = Utils::split(line, ',');

    if (fields.size() < 6)
    {
        throw std::runtime_error("字段不足（至少需要 6 个字段）");
    }

    std::string type  = Utils::trim(fields[0]);
    std::string id    = Utils::trim(fields[1]);
    std::string name  = Utils::trim(fields[2]);
    int         age   = std::stoi(Utils::trim(fields[3]));
    std::string info1 = Utils::trim(fields[4]);
    std::string info2 = Utils::trim(fields[5]);

    if (type == "S")
    {
        // 学生: info1=专业, info2=成绩
        double score = std::stod(info2);
        return std::make_unique<Student>(id, name, age, info1, score);
    }
    else if (type == "T")
    {
        // 教师: info1=职称, info2=科目
        return std::make_unique<Teacher>(id, name, age, info1, info2);
    }
    else
    {
        throw std::runtime_error("未知类型: " + type);
    }
}
