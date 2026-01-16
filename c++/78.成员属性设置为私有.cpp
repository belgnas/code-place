// 成员属性设置为私有

// 优点：
// 1. 将所有成员属性设置为私有，可以自己控制读写权限
// 2. 对于写权限，我们可以检测数据的有效性

#include<iostream>
#include<cstring>
using namespace std;

class Person
{
// 通过公共部分来实现
public:
    //设置姓名
    void setName(string name)
    {
        m_Name = name;
    }
    //获取姓名
    string getName()
    {
        return m_Name;
    }

    //获取年龄
    int getAge()
    {
        return m_Age;
    }
    //设置年龄（ 0 ~ 150 ）
    void setAge(int age)
    {
        if(age < 0 || age > 150)
        {
            cout << "年龄输入有误(不在 0 ~ 150 之间)，赋值(修改)失败" << endl;
            return;
        }
        m_Age = age;
    }

    //设置偶像
    void setIdol(string idol)
    {
        m_Idol = idol;
    }

private:
    string m_Name; // 姓名 可读可写

    int m_Age = 18; // 年龄(默认18) 只读  也可以写（年龄必须在 0 ~ 150 之间）

    string m_Idol = "小狐娘"; // 偶像 只写
    // 外部代码只能通过 setIdol 函数来对其进行赋值操作，无法直接获取该变量的值，体现了只写的属性访问控制特性


};

int main()
{
    Person p1;
    //姓名设置
    p1.setName("张三");
    cout << "姓名：" << p1.getName() << endl;

    //年龄设置
    // p1.setAge(20);
    // p1.m_Age = 20;
    p1.setAge(160);
    cout << "年龄：" << p1.getAge() << endl;

    //偶像设置
    p1.setIdol("小猫");
    // cout << "偶像：" << p1.getIdol << endl; // 只写状态，外界访问不到

    return 0;
}