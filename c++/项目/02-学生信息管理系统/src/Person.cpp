// Person.cpp — 人类抽象基类实现

#include"Person.h"

Person::Person(const std::string& id, const std::string& name, int age)
    : m_Id(id), m_Name(name), m_Age(age)
{
}
