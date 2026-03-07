//二维数组应用案例-考试成绩统计

//目标：请分别输出三位同学的总成绩

//         语文        数学          英语
//张三      100        100           100
//李四      90         50            100
//王五      60         70            80

#include<iostream>
#include<string>//用字符串string记得加这个头文件
using namespace std;

int main()
{
    int scores[3][3] =
    {
        {100,100,100},
        {90,50,100},
        {60,70,80}
    };

    string name[3] = {"张三","李四","王五"};

    for (int i = 0; i < 3; i++)
    {
        int sum = 0;//统计分数总和变量
        for (int j = 0; j < 3; j++)
        {
            sum += scores[i][j];
            cout << scores[i][j]<<"   ";
        }
        cout << "第" << i + 1 <<  "个人"<< name[i] << "的总分为："<< sum << endl;
        cout << endl;
    }
    

    system("pause");
    return 0;
}