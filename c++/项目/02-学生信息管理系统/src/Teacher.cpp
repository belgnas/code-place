// Teacher.cpp — 教师类实现

#include"Teacher.h"
#include<iomanip>
#include<sstream>

Teacher::Teacher(const std::string& id, const std::string& name, int age,
                 const std::string& title, const std::string& course)
    : Person(id, name, age)
    , m_Title(title)
    , m_Course(course)
{
}

void Teacher::display() const
{
    std::cout << "+-----------------------------+" << std::endl;
    std::cout << "| [教师] " << std::left << std::setw(24) << m_Name  << "|" << std::endl;
    std::cout << "| 工号: " << std::setw(23) << m_Id    << "|" << std::endl;
    std::cout << "| 年龄: " << std::setw(23) << m_Age   << "|" << std::endl;
    std::cout << "| 职称: " << std::setw(23) << m_Title << "|" << std::endl;
    std::cout << "| 科目: " << std::setw(23) << m_Course << "|" << std::endl;
    std::cout << "+-----------------------------+" << std::endl;
}

std::string Teacher::toCSV() const
{
    // 格式: 类型,ID,姓名,年龄,专业/职称,成绩/科目
    std::ostringstream oss;
    oss << "T," << m_Id << "," << m_Name << "," << m_Age
        << "," << m_Title << "," << m_Course;
    return oss.str();
}
