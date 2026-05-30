#include<iostream>
using namespace std;
int main()
{
    int n,m;
    cin >> n >> m;
    int arr[n];
    int brr[m];
    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    for(int i = 0; i < m; i++)
    {
        cin >> brr[i];
    }
    int a_num = 0;
    int b_num = 0;
    // 循环直到两个数组都遍历完
    while(a_num < n || b_num < m)
    {
        // 当两个数组都还有元素时进行比较输出
        if(a_num < n && b_num < m)
        {
            if(arr[a_num] <= brr[b_num])
            {
                cout << arr[a_num] << " ";
                a_num++;
            }
            else
            {
                cout << brr[b_num] << " ";
                b_num++;
            }
        }
        // 当arr数组还有元素但brr数组已经遍历完，输出arr剩余元素
        else if(a_num < n)
        {
            cout << arr[a_num] << " ";
            a_num++;
        }
        // 当brr数组还有元素但arr数组已经遍历完，输出brr剩余元素
        else if(b_num < m)
        {
            cout << brr[b_num] << " ";
            b_num++;
        }
    }
    /*
    for(int i = 0; a_num < n || b_num < m; i++)
    {
        if(arr[a_num] <= brr[b_num] && a_num < n)
        {
            cout << arr[a_num] << " ";
            a_num++;
        }
        else if(arr[a_num] > brr[b_num] && b_num < m)
        {
            cout << brr[b_num] << " ";
            b_num++;
        }
    }
    */
    

    return 0;
}