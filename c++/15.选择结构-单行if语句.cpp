//选择结构-单行if语句

#include<iostream>
using namespace std;

int main()
{
    //1.用户输入分数
    int score=0;
    cout<<"请输入一个分数："<<"\n";
    cin>>score;

    //2.打印用户输入的分数
    cout<<"你输入的分数为："<<score<<"\n";

    //3.判断用户的分数是否大于500，如果大于，那么输出
    if(score>500)//ps：if后面不要加;否则if无效
    {
        cout<<"还可以，加油！"<<"\n";
    }
    
    system("pause");

    return 0;   
}