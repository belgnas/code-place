//结构体-结构体案例-校内师生信息分类

/*

学校正在做毕设项目，每名老师带领5个学生，总共有3名老师，需求如下：

设计学生和老师的结构体，其中在老师的结构体中，有老师姓名和一个存放5名学生的数组作为成员，
学生的成员有姓名、考试分数，创建数组存放3名老师，通过函数给每个老师及所带的学生赋值，
最终打印出老师数据以及老师所带的学生数据。

*/

#include<iostream>
#include<string>
#include<ctime>
using namespace std;

struct Student
{
    string sName;
    int score;
};

struct Teacher
{
    string tName;//教师姓名
    Student sArray[5];
    //stu是Teacher结构体中的一个成员，类型为Student结构体
};


//创建一个给老师和学生赋值的函数
void allocateSpace(struct Teacher tArray[] , int len )
{

    string nameSeed = "ABCDE";

    //给老师开始赋值
    for (int i = 0; i < len; i++)
    {
        tArray[i].tName = "Teacher_";
        tArray[i].tName += nameSeed[i];
        //依次命名为nameSeed的每一位

        //通过循环给每名老师所带的学生信息赋值
        for (int j = 0; j < 5; j++)
        {
            tArray[i].sArray[j].sName = "Student_";//这里的\t是缩进
            tArray[i].sArray[j].sName += nameSeed[j];
            //这里的“.”相当于所属关系

            int random = rand() % 61 + 40; // 随机数：40~100
            tArray[i].sArray[j].score = random;
        }        
    }
}

//打印所有的信息
void printInfo(struct Teacher tArray[] , int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << "老师姓名：" << tArray[i].tName << endl;

        for (int j = 0; j < 5; j++)
        {
            cout << "\t学生姓名：" << tArray[i].sArray[j].sName << "";//这里的\t是缩进
            cout << " 考试分数：" << tArray[i].sArray[j].score << endl;
        }
        
    }
    
}

int main()
{
    srand((unsigned int)time(NULL));//添加随机数种子，利用当前系统时间生成随机数，防止一样

    //1.创建3名老师的的数组
    struct Teacher tArray[3];

    //2.通过函数给3名老师的信息赋值，并给老师带的学生信息赋值
    int len = sizeof(tArray) / sizeof(tArray[0]);
    allocateSpace(tArray,len);

    //3.打印所有老师及所带的学生信息
    printInfo(tArray,len);


    system("pause");

    return 0;   
}