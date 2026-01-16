//指针-指针和数组

//作用：利用指针访问数组中的元素

#include<iostream>
using namespace std;

int main()
{
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};

    //一般方法
    cout << "第一个元素为：" << arr[0] << endl;

    //利用指针来访问数组中的元素
    int * p = arr;//arr就是数组首地址

    cout << "利用指针来访问第1个元素：" << * p << endl;

    p++;//让指针向后偏移"sizeof(int)"个字节

    cout << "利用指针来访问第2个元素：" << * p << endl;

    //利用指针来输出整个数组
    int * p2 = arr;
    for (int i = 0; i < 10; i++)
    {
        cout << * p2 << endl;
        p2++;
    }
    
    system("pause");

    return 0;   
}