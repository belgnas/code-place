//结构体-结构体中const使用的场景

//作用：用const来防止出现改变外部函数的误操作

#include<iostream>
#include<string>
using namespace std;

struct Student
{
    string name;
    int age;
    int score;
};

//加上一个const,一旦有修改的操作就会报错，这样可以防止误操作
void printStudent(const struct  Student * s)
{
    //可以防止出现像下面一行这样子的误操作
    //s->name = "小李";
    cout << "姓名：" << s->name << "  年龄：" << s->age << "  分数：" << s->score << endl;

}


int main()
{
    //创建结构体变量
    struct Student s = { "小郑" , 17 , 80 };

    printStudent(&s);
    
    system("pause");

    return 0;   
}