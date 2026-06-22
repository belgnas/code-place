// Student.cpp — 学生类实现

#include"Student.h"
#include<iomanip>
#include<sstream>

Student::Student(const std::string& id, const std::string& name, int age,
                 const std::string& major, double score)
    : Person(id, name, age)
    , m_Major(major)
    , m_Score(score)
{
}

void Student::display() const
{
    std::cout << "+-----------------------------+" << std::endl;
    std::cout << "| [学生] " << std::left << std::setw(24) << m_Name << "|" << std::endl;
    std::cout << "| 学号: " << std::setw(23) << m_Id    << "|" << std::endl;
    std::cout << "| 年龄: " << std::setw(23) << m_Age   << "|" << std::endl;
    std::cout << "| 专业: " << std::setw(23) << m_Major << "|" << std::endl;
    std::cout << "| 成绩: " << std::setw(23) << m_Score << "|" << std::endl;
    std::cout << "| 评级: " << std::setw(23) << getGrade() << "|" << std::endl;
    std::cout << "+-----------------------------+" << std::endl;
}

std::string Student::toCSV() const
{
    // 格式: 类型,ID,姓名,年龄,专业/职称,成绩/科目
    std::ostringstream oss;
    oss << "S," << m_Id << "," << m_Name << "," << m_Age
        << "," << m_Major << "," << m_Score;
    return oss.str();
}

std::string Student::getGrade() const
{
    if      (m_Score >= 90) return "A (优秀)";
    else if (m_Score >= 80) return "B (良好)";
    else if (m_Score >= 70) return "C (中等)";
    else if (m_Score >= 60) return "D (及格)";
    else                    return "F (不及格)";
}
