//结构体-结构体的定义与使用

//语法：struct 结构体名 { 结构体成员列表 };

//通过结构体创建变量的方式有3种（一般使用前2种）
//1.struct 结构体名 变量名
//2.struct 结构体名 变量名 = {成员1值, 成员2值...}
//3.定义结构体时顺便创建变量

#include<iostream>
#include<string>
using namespace std;


//定义学生数据类型：学生包括（姓名，年龄，分数）
//个人理解：自定义数据类型：一些类型的集合组成的一个类型
//语法 struct 类型名称 { 成员列表 }
struct Student//定义结构体这里的 struct 关键字不可以可以省略
{
    //成员列表
    //姓名
    string name;
    //年龄
    int age;
    //分数
    int score;
}s3;//注意这里的分号！
//3.定义结构体时顺便创建变量（在这里）


//通过学生类型创建具体学生
int main()
{
    //1.struct 结构体名 变量名
    struct Student s1;//创建结构体的 struct 关键字可以可以省略
    //给s1属性赋值，通过.访问结构体变量中的属性
    s1.name = "张三";
    s1.age = 18;
    s1.score = 100;

    cout << "姓名：" << s1.name << "  年龄：" << s1.age << "  分数：" << s1.score << endl;

    //2.struct 结构体名 变量名 = {成员1值, 成员2值...}
    struct Student s2 = { "李四" , 18 , 80 };

    cout << "姓名：" << s2.name << "  年龄：" << s2.age << "  分数：" << s2.score << endl;

    //3.定义结构体时顺便创建变量（在前面定义结构体的末尾）
    s3.name = "王五";
    s3.age = 20;
    s3.score = 60; 

    cout << "姓名：" << s3.name << "  年龄：" << s3.age << "  分数：" << s3.score << endl;

    
    system("pause");
    return 0;   
}