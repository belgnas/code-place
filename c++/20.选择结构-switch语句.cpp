//选择结构-switch语句

//作用：执行多条件分支语句

//ps：1.case里如果没有break，那么会一直向下执行（意思就是要加上break）
//    2.判断的时候只能是整型或字符型，不可以是一个区间或其他数据类型（如浮点型）

//if和switch的区别
//缺点：判断的时候只能是整型或字符型，不可以是一个区间
//优点：结构清晰，执行效率高

#include<iostream>
using namespace std;

int main()
{
    //给一个电影打分
    //9 ~ 10分：经典
    //7 ~ 8 分：非常好 
    //5 ~ 6 分：一般
    //5 分以下：烂片

    //1.提示用户开始打分
    cout<<"请给这个电影打分"<<endl;

    //2.用户输入的分数
    int score=0;
    cin>>score;
    cout<<"你打的分数为："<<score<<endl;

    //3.根据用户输入的分数来显示结果
    switch(score)
    {
        case 10:
            cout<<"经典电影"<<endl;
            break;//退出当前分支
        case 9:
            cout<<"经典电影"<<endl;
            break;
        case 8:
            cout<<"非常好"<<endl;
            break;
        case 7:
            cout<<"非常好"<<endl;
            break;
        case 6:
            cout<<"一般"<<endl;
            break;
        case 5:
            cout<<"一般"<<endl;
            break;
        default:
            cout<<"烂片"<<endl;
            break;
    } 

    
    system("pause");

    return 0;   
}