// 2025/2/22

// 归并排序

#include<iostream>

using namespace std;

const int N = 10010;

int n;
int arr[N];
int tmp[N]; // 临时数组

void merge_sort(int arr[], int l, int r)
{
    if(l >= r) return;

    int mid = (l + r) >> 1; // 相当于除以 2
    // 这里相较于快排先递归是因为我需要先找到每一小小块（只含1个元素），然后按照规律合并各个小数组
    merge_sort(arr, l, mid);
    merge_sort(arr, mid + 1, r);

    int k = 0; // temp临时数组（指向第一个元素的位置，意思是此时 tmp 数组为空的）
    int i = l; // 左边数组的指针起点时 l
    int j = mid + 1; // 右边数组的起点是 mid + 1
    while(i <= mid && j <= r) // 当左边的数组和右边的数组都还有数字时
    {
        if(arr[i] <= arr[j]) // 左右指针的数字哪个比较大，那个就赋值给 tmp 临时数组
        {
            tmp[k] = arr[i];
            k++;
            i++;
        }
        else
        {
            tmp[k] = arr[j];
            k++;
            j++;
        }
    }

    while(i <= mid) // 看看左边的数组有没有剩余
    {
        tmp[k] = arr[i];
        k++;
        i++;
    }
    while(j <= r) // 再看看右边的数组有没有剩余（这里是偷懒就没写判断直接从重复写了，反正没影响）
    {
        tmp[k] = arr[j];
        k++;
        j++;
    }

    for(int i = l, j = 0; i <= r; i++, j++) // 将排序好的 tmp 数组拷贝到原数组中
    {
        arr[i] = tmp[j];
    }
}

int main()
{
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    merge_sort(arr, 0, n - 1);

    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}