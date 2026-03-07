//跳转语句-break语句

//作用：用于跳出选择结构或者循环结构

//break使用的时机：
//1.出现在switch条件语句中，作用是终止case并跳出switch
//2.出现在循环语句中，作用是跳出当前的循环语句
//3.出现在嵌套循环中，跳出最近的内层循环结构

#include<iostream>
using namespace std;

int main()
{
    //出现在switch语句中
/*

    cout<<"转生到异世界，选择你的种族"<<endl;
    cout<<"1.人类族"<<endl;
    cout<<"2.半精灵"<<endl;
    cout<<"3.半龙族"<<endl;

    int select=0;//创建一个选择结果的变量

    cin>>select;//等待输入

    switch (select)
    {
    case 1:
        cout<<"已选择成为人类族"<<endl;
        break;
    case 2:
        cout<<"已选择成为半精灵"<<endl;
        break;
    case 3:
        cout<<"已选择成为半龙族"<<endl;
        break;
    
    default:
        cout<<"无效选择，死亡""\n";
        break;
    }

*/



    //出现在循环语句中
/*

    for (int i = 0; i < 10; i++)
    {
        if (i==5)
        {
            break;
        }
        
        cout<<i<<endl;
    }

*/

    //出现在嵌套语句中
    for (int j = 0; j < 10; j++)
    {
        for (int k = 0; k < 10; k++)
        {
            if (k==5)
            {
                break;//退出内层循环
            }
            
            cout<<"*"<<"\t";
        }
        cout<<endl;
    }
    
    
    system("pause");

    return 0;   
}