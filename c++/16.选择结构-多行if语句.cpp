//选择结构：多行if语句

//if（条件）{条件满足时执行的语句}else{条件不满足时执行的语句}

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

    //3.判断用户的分数是否大于500，如果大于，那么输出“还可以，加油”，否则输出“没事的，加油”
    if(score>500)//大于500分执行下面大括号的内容
    {
        cout<<"还可以，加油！"<<"\n";
    }
    else//小于等于500分执行else下面大括号的内容
    {
        cout<<"没事的，加油"<<"\n";
    }

    system("pause");

    return 0;   
}