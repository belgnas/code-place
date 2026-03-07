// 2025/2/25

// 快排的思路：
// 1. 先找到一个基准值，一般是第一个值
// 2. 然后定义两个指针，一个指向第一个值，一个指向最后一个值
// 3. 然后左指针向右移动，右指针向左移动，直到左指针指向的值大于基准值，右指针指向的值小于基准值
// 4. 然后交换左指针和右指针指向的值

// 有一个反转其排序顺序的非常作弊的方法：可以将传入的数组里的每个数处理一下变成其负数，然后再进行快排，最后再将每个数处理一下变成其正数

#include<iostream>

using namespace std;

const int N = 100010;

int n;
int arr[N];

void quick_sort(int arr[], int l, int r)
{
    if(l >= r) return;

    int x = arr[l];
    int i = l - 1;
    int j = r + 1;

    while(i < j)
    {
        do i++; while(arr[i] < x);
        do j--; while(arr[j] > x);
        if(i < j) swap(arr[i], arr[j]);
    }

    quick_sort(arr, l, j);
    quick_sort(arr, j + 1, r);
}

int main()
{
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    quick_sort(arr, 0, n - 1);

    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}