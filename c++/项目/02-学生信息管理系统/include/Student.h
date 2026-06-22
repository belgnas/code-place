// Student.h — 学生类（继承 Person）
// 增加学号、专业、成绩等学生特有属性

#pragma once
#include"Person.h"
#include<string>
#include<vector>

class Student : public Person
{
public:
    Student(const std::string& id, const std::string& name, int age,
            const std::string& major, double score);

    // 实现纯虚函数
    void display() const override;
    std::string getRole() const override { return "学生"; }
    std::string toCSV() const override;

    // 学生特有 getter/setter
    std::string getMajor() const { return m_Major; }
    double      getScore() const { return m_Score; }
    void setMajor(const std::string& major) { m_Major = major; }
    void setScore(double score) { m_Score = score; }

    // 成绩评级
    std::string getGrade() const;

private:
    std::string m_Major;     // 专业
    double      m_Score;     // 成绩 (0-100)
};
