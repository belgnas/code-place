//结构体-结构体数组

//作用：将自定义的结构体放入到数组中方便维护

//语法：struct 结构体名 数组名[元素个数] = { {}，{}，...} }

#include<iostream>
#include<string>
using namespace std;

//1.定义结构体
struct Student
{
    //成员列表
    //姓名
    string name;
    //年龄
    int age;
    //分数
    int score;
};

int main()
{
    //2.创建结构体数组
    struct Student stuArray[3] = 
    {
        {"张三", 18 , 100},
        {"李四", 28 , 99},
        {"王五", 38 , 60}

    };

    //3.给结构体数组中的元素赋值(修改赋值)
    stuArray[2].name = "赵六";
    stuArray[2].age = 50;
    stuArray[2].score = 70;

    for (int i = 0; i < 3; i++)
    {
        cout << "姓名：" << stuArray[i].name << "  年龄：" << stuArray[i].age << "  分数：" << stuArray[i].score << endl;

    }
    

   
    
    system("pause");

    return 0;   
}