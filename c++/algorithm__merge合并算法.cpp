//merge合并算法

//语法：
//merge(第一个序列的起始迭代器, 第一个序列的终止迭代器, 第二个序列的起始迭代器, 第二个序列的终止迭代器, 目标序列的起始迭代器，用于存储合并后的结果)


/*
    要求
    1. 两个输入序列必须是已排序的。通常情况下，排序的顺序应该是一致的（都是升序或都是降序）。
    2. 输入序列的迭代器类型应该支持比较操作，以便函数能够确定元素的顺序。
    3. 目标序列的迭代器类型应该支持写入操作，以便能够将合并后的元素存储到目标序列中。
*/
#include<iostream>
#include<algorithm>//必要头文件
using namespace std;
int main()
{
    int arr[3] = {1,3,5};
    int brr[3] = {2,4,6};
    int crr[6] = {0};
    merge(arr, arr+3, brr, brr+3, crr);
    for(int i = 0; i < 6; i++)
    {
        cout << crr[i] << endl;
    }

    
    return 0;
}