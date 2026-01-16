//类和对象-封装-属性和行为作为整体
//（创建一个学生类，输入学号和姓名，并输出）

#include<iostream>
#include<cstring>
using namespace std;

//创建一个学生类，输入学号和姓名，并输出

class Student
{
public://公共权限

    // 类中的属性和行为 我们统一称为 成员
    //属性  成员属性 成员变量
    //行为  成员函数 成员方法

    //属性
    string m_Name; // 姓名
    int m_Id; // 学号

    //行为
    //显示姓名和学号
    void showStudent()
    {
        cout << "姓名：" << m_Name << " 学号：" << m_Id << endl;
    }


    // 给姓名赋值
    void setName(string name)
    {
        m_Name = name;
    }

    //给学号赋值
    void setId(int Id)
    {
        m_Id = Id;
    }

};

int main()
{
    //创建一个具体的学生 实例化对象
    Student s1,s2;

    //给s1对象 进行属性赋值操作
    // 1.
    s1.m_Name = "张三";
    s1.m_Id = 1;
    // 2.
    s2.setName("李四");
    s2.setId(2);

    //显示学生信息
    s1.showStudent();
    s2.showStudent();

    return 0;
}
