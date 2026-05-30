//找数组中的最大值

//原理：如果访问的数值中的元素比我认定的大，更新最大值

#include<iostream>
using namespace std;

int main()
{
    int arr[6]={300,350,999,200,400,250};

    int max=0;
    for (int i = 0; i < 5; i++)
    {
        if (arr[i]>max)
        {
            max=arr[i];
        }
        
    }

    cout<<"最大值为："<<max<<endl;
        

    system("pause");

    return 0;
}