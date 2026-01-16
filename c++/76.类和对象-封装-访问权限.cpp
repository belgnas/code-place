//类和对象-封装-访问权限

//封装的意义二：
//类在设计时，可以把属性和行为都放在不同的权限下，加以控制

//访问的权限有三种：
// 1. public    公共权限：类内可以访问 类外可以访问
// 2. protected 保护权限：类内可以访问 类外不可以访问 (儿子可以访问父亲中的保护内容)
// 3. private   私有权限：类内可以访问 类外不可以访问 (儿子不可以访问父亲的私有内容)

#include<iostream>
#include<cstring>
using namespace std;

class Person
{
public:
    //公共权限
    string m_Name; // 姓名

protected:
    //保护权限
    string m_birthday; // 生日

private:
    //私有权限
    int m_Password; // 银行卡密码

private: // 私有权限 (类外不可以访问)
    void func()
    {
        m_Name = "张三";
        m_birthday = "11月1日";
        m_Password = 123456;
    }


};

int main()
{
    //实例化具体对象
    Person p1;

    p1.m_Name = "李四";
    // p1.m_birthday = "12月1日"; //  保护权限内容，在类外访问不到
    // p1.m_Password = 123; //  私有权限内容，在类外访问不到

    // p1.func();

    return 0;
}