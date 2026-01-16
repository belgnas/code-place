//结构体-结构体变量

//作用：通过指针访问结构体中的成员

//利用操作符 -> 可以通过结构体指针访问结构体属性

#include<iostream>
using namespace std;

//1.定义结构体
struct Student
{
    string name;
    int age;
    int score;
};


int main()
{
    //2.创建学生结构体变量
    struct Student s = {"张三", 18 , 100};

    //3.通过指针指向结构体变量
    struct Student * p = &s;

    //4.通过指针访问结构体变量中的数据
    cout << "姓名：" << p->name << "  年龄：" << p->age << "  分数：" << p->score << endl;//使用s.name这种方式也可以（不是本章知识点，忘了是什么时候讲的了）
    
    system("pause");

    return 0;   
}