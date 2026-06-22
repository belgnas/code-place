// Person.h — 抽象人类基类
// 提供所有"人"的公共属性和接口
// 多态：通过基类指针统一管理 Student 和 Teacher

#pragma once
#include<string>
#include<iostream>
#include<memory>

// 人类抽象基类
class Person
{
public:
    // 构造与析构
    Person(const std::string& id, const std::string& name, int age);
    virtual ~Person() = default;

    // 纯虚函数 — 派生类必须实现
    virtual void display() const = 0;
    virtual std::string getRole() const = 0;
    virtual std::string toCSV() const = 0;  // 序列化为 CSV 行

    // 公共 getter
    std::string getId()   const { return m_Id; }
    std::string getName() const { return m_Name; }
    int         getAge()  const { return m_Age; }

    // 公共 setter
    void setName(const std::string& name) { m_Name = name; }
    void setAge(int age) { m_Age = age; }

    // 运算符重载：按学号比较
    bool operator==(const Person& other) const { return m_Id == other.m_Id; }

protected:
    std::string m_Id;
    std::string m_Name;
    int         m_Age;
};
