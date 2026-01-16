//选择结构-嵌套if语句

//在if语句中可以嵌套使用if语句，达到更精确的条件判断

#include<iostream>
using namespace std;

int main()
{
    //1.用户输入分数
    int score=0;
    cout<<"请输入一个分数：\n";
    cin>>score;

    //2.打印用户输入的分数
    cout<<"你输入的分数为："<<score<<"\n";

    //3.判断用户的分数
    //大于500：还可以，加油
        //大于590：深大
        //大于560：广工
        //大于540：哈理工
        //大于500：普通一本
    //大于400：在大学要加油
    //小于等于400：没事的，加油
    if(score>500)
    {
        cout<<"还可以，加油！"<<"\n";
        if(score>=590)
        {
            cout<<"考上了深圳大学，你是不是开挂了"<<"\n";
        }
        else if(score>=560)
        {
            cout<<"考上了广东工业大学，你很优秀"<<"\n";
        }
        else if(score>=540)
        {
            cout<<"考上了哈尔滨理工大学，只要你努力，你绝对不会比深大和广工的差的"<<"\n";
        }
        else
        {
            cout<<"考上了普通的一本"<<"\n";
        }
    }
    else if(score>400)
    {
        cout<<"在大学要加油！"<<"\n";
    }
    else
    {
        cout<<"没事的，加油！"<<"\n";
    }
    
    system("pause");

    return 0;   
}