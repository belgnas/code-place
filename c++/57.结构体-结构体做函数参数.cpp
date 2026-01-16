//结构体-结构体做函数参数

//作用：将结构体作为参数向函数中传递

//传递的方式有2种
//1.值传递
//2.地址传递

//区别：值传递不会修改主函数中的值，而地址传递会修改

//1.如果不想修改主函数中的数据，用值传递，反之用地址传递
//2.地址传递会极大地节省需要的运行内存空间：
//  因为值传递需要拷贝整个结构体中的值，但是地址传递只需要拷贝一份地址（4/8个字节）

//  可以用地址传递加上一个const来达到和值传递一样的效果，并且更节省内存空间

#include<iostream>
using namespace std;

struct Student
{
    string name;
    int age;
    int score;
};

//打印学生信息的函数
//1.值传递
void printStudent1(struct Student s)
{
    s.score = 100;
    cout << "子函数1中 姓名：" << s.name << "  年龄：" << s.age << "  分数：" << s.score << endl;

}

//2.地址传递(ps:这里是->)
void printStudent2(struct Student *p)
{
    p->score= 100;
    cout << "子函数2中 姓名：" << p->name << "  年龄：" << p->age << "  分数：" << p->score << endl;

}

int main()
{
    //将学生传入到一个参数中，打印学生身上的所有信息   
    struct Student s;
    s.name = "小李";
    s.age = 18;
    s.score = 70;

    printStudent1(s);
    cout << "main函数中 姓名：" << s.name << "  年龄：" << s.age << "  分数：" << s.score << endl;


    printStudent2(&s);

    cout << "main函数中 姓名：" << s.name << "  年龄：" << s.age << "  分数：" << s.score << endl;



    system("pause");

    return 0;   
}