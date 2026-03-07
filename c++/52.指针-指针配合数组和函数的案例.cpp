//指针-指针配合数组和函数的案例

//案例描述：封装一个函数，利用冒泡排序，实现对整型数组的升序排序

#include<iostream>

using namespace std;

//冒泡排序函数   参数1：数组的首地址、参数2：数组长度
void bubbleSort(int * arr,int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            //如果 j > j+1 的值  交换数字
            if ( arr[j] > arr[j+1] )
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
            
        }
        
    }
    
}

//打印数组函数
void printArray(int * arr,int len)
{
    for (int k = 0; k < len; k++)
    {
        cout << arr[k] << endl;
    }
    
}

int main()
{
    //1.先创建一个数组
    int arr[10] = {4,5,6,3,9,1,2,10,8,7,};

    //数组长度
    int len = sizeof(arr)/sizeof(arr[0]);
    
    //2.创建一个函数，实现冒泡排序
    bubbleSort(arr,len);

    //3.打印排序后的数组 
    //创建一个函数，实现打印数组
    printArray(arr,len);
    
    
    system("pause");

    return 0;   
}