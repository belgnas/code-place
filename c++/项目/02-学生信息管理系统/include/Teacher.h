// Teacher.h — 教师类（继承 Person）
// 增加工号、职称、授课科目等教师特有属性

#pragma once
#include"Person.h"
#include<string>

class Teacher : public Person
{
public:
    Teacher(const std::string& id, const std::string& name, int age,
            const std::string& title, const std::string& course);

    // 实现纯虚函数
    void display() const override;
    std::string getRole() const override { return "教师"; }
    std::string toCSV() const override;

    // 教师特有 getter/setter
    std::string getTitle()  const { return m_Title; }
    std::string getCourse() const { return m_Course; }
    void setTitle(const std::string& title)  { m_Title = title; }
    void setCourse(const std::string& course){ m_Course = course; }

private:
    std::string m_Title;     // 职称（讲师/副教授/教授）
    std::string m_Course;    // 授课科目
};
