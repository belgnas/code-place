//二维数组-定义方式

//定义方式：
//1.数据类型 数据名[行数][列数];
//2.数据类型 数据名[行数][列数]={{数据1,数据2},{数据3,数据4,数据5}};
//3.数据类型 数据名[行数][列数]={数据1,数据2,数据3,数据4};
//4.数据类型 数据名[][列数]={数据1,数据2,数据3,数据4};

//！重要！
//建议：利用第2种更加直观，提高代码的可读性

#include<iostream>
using namespace std;

int main()
{
    //1.数据类型 数据名[行数][列数];
    int arr[2][3];//2行3列
    arr[0][0]=1;
    arr[0][1]=2;
    arr[0][2]=3;
    arr[1][0]=4;
    arr[1][1]=5;
    arr[1][2]=6;

    cout<<arr[0][0]<<endl;
    cout<<arr[0][1]<<endl;
    cout<<arr[0][2]<<endl;
    cout<<arr[1][0]<<endl;
    cout<<arr[1][1]<<endl;
    cout<<arr[1][2]<<endl;
    cout<<endl;

    //利用循环来打印二维数组
    //外层循环打印行数，内层循环打印列数
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout<<arr[i][j]<<endl;
        }
        
    }

    cout<<endl;

    
//尽量用这个！！！
//！！！！！！！！
    //2.数据类型 数据名[行数][列数]={{数据1,数据2,数据3},{数据4,数据5}};
    //优点：更直观！
    int brr[2][3]=
    {
        {1,2,3},
        {4,5,6}
    };

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout<<brr[i][j]<<" ";
        }
        cout << endl;    
    }
    cout<<endl;


    //3.数据类型 数据名[行数][列数]={数据1,数据2,数据3,数据4};
    int crr[2][3]={1,2,3,4,5,6};

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout<<crr[i][j]<<" ";
        }
        cout << endl;    
    }
    cout<<endl;
    
    //4.数据类型 数据名[][列数]={数据1,数据2,数据3,数据4};
    int drr[][3]={1,2,3,4,5,6};
    //定义数组的时候一定不可以缺少列数

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout<<drr[i][j]<<" ";
        }
        cout << endl;    
    }
    cout<<endl;
    
    
    system("pause");

    return 0;   
}