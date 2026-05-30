//类和对象-封装-属性和行为作为整体-自己的练习（创建一个学生类，输入学号和姓名，并输出）


#include<iostream>
#include<cstring>
using namespace std;

class Student
{
public://公共权限

    string S_name;

    string Student_name()
    {
        return S_name;
    }

    string S_numble;

    string Student_numble()
    {
        return S_numble;
    }


};

int main()
{
    Student xuesheng;

    cout << "请输入名字：" << endl;
    cin >> xuesheng.S_name ;
    cout << "请输入学号：" << endl;
    cin >> xuesheng.S_numble;

    cout << "名字是：" << xuesheng.S_name << endl;
    cout << "学号是：" << xuesheng.S_numble << endl;

    return 0;
}