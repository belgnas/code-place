//一维数组-数组名

//一维数组名称的用途：
//1.可以统计整个数组在内存中的长度
//2.可以获取数组在内存中的首地址

#include<iostream>
using namespace std;

int main()
{
    //1.可以统计整个数组在内存中的长度
  
    int arr[]={1,2,3,4,5};
    cout<<"整个数组占用的内存空间为："<<sizeof(arr)<<endl;
    cout<<"每个元素占用的内存空间为："<<sizeof(arr[0])<<endl;//int（整型）占用的内存大小为4字节
    cout<<"数组中元素个数为："<<sizeof(arr)/sizeof(arr[0])<<endl;

    //2.可以获取数组在内存中的首地址
    //这里可以看出数组内元素的地址是连续的
    cout<<"数组的首地址为："<<arr<<endl;//ps：默认输出16进制的位置
    cout<<"数组的首地址为："<<(long long)arr<<endl;//ps：这里arr前面的()作用是将默认的16进制的位置转化成10进制数字，其中()里面填写int可能会出现长度超了的情况，改成long long即可
    cout<<"数组中第一个元素的地址为："<<(long long)&arr[0]<<endl;
    //ps:&是取址符，若是需要查看具体元素的地址，必须要加& 
    cout<<"数组中第二个元素的地址为："<<(long long)&arr[1]<<endl;
    cout<<"数组中第三个元素的地址为："<<(long long)&arr[2]<<endl;

    //arr=100错误，数组名是常量，因此不可以赋值

    system("pause");
    
    return 0;
}