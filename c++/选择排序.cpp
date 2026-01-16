// 选择排序

#include <iostream>
using namespace std;

int main()
{
    int arr[9] = {4, 2, 0, 5, 5, 7, 1, 3, 9};
    cout << "排序前：" << endl;
    for (int i = 0; i < 9; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < 9 - 1; i++)
    {
        int num = i;
        for (int j = i + 1; j < 9; j++)
        {
            if(arr[j] < arr[num])
            {
                num = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[num];
        arr[num] = temp;
    }

    // 打印排序后的数组
    cout << "排序后：" << endl;
    for (int i = 0; i < 9; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;


    return 0;
}