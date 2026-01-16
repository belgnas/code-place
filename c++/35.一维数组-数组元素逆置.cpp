//数组元素逆置

#include<iostream>
using namespace std;

int main()
{
    //1.创建数组
    int arr[5]={1,2,3,4,5};
    cout<<"数组逆置前："<<endl;
    for (int i=0;i<5;i++)
    {
        cout<<arr[i];
    }
    cout<<endl;
    
    //2.实现逆置

    //记录起始下标位置
    int start=0;
    //记录结束下标位置
    int end=sizeof(arr)/sizeof(arr[0])-1;//这里-1是因为数组下标是从 0 开始的，为了得到的是最后一个元素的下标，需要-1

    while (start<end)
    {
    
    //实现元素互换
    int temp=arr[start];
    arr[start]=arr[end];
    arr[end]=temp;

    //下标更新
    start++;
    end--;
    }

    //3.打印逆置后的数组
    cout<<"数组元素逆置后："<<endl;
    for (int i=0;i<5;i++)
    {
        cout<<arr[i];
    }
    cout<<endl;
    
    
    system("pause");
    return 0;
}