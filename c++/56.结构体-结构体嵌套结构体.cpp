//结构体-结构体嵌套结构体

//作用：结构体中的成员可以是亮一个结构体

//例如：每个老师辅导一个学员，一个老师的结构体中，记录一个学生的结构体

#include<iostream>
#include<string>
using namespace std;

struct Student
{
    string name;//学生名字
    int age;//学生年龄
    int score;//学生分数

};

struct Teacher
{
    int id;//教师编号
    string name;//教师姓名
    int age;//教师年龄
    Student stu;//教师带的学生（需要先定义学生的结构体）
    //stu是Teacher结构体中的一个成员,，类型为Student结构体
};


int main()
{
    //创建老师
    struct Teacher t;
    t.id = 10000;
    t.name = "老王";
    t.stu.name = "小王";//注意：这里有2个.
    t.stu.age = 20;
    t.stu.score = 60;

    //下面这样也可以
    //Teacher t = {10000, "老王", 40, {"小王", 20, 60}};

    cout << "教师编号：" << t.id << endl;
    cout << "教师姓名：" << t.name << endl;
    cout << "教师年龄：" << t.age << endl;
    cout << "学生名字：" << t.stu.name << endl;
    cout << "学生年龄：" << t.stu.age << endl;
    cout << "学生分数：" << t.stu.score << endl;

    
    system("pause");

    return 0;   
}