// 2025/2/22

// πÈ≤¢≈≈–Ú

#include<iostream>
using namespace std;
const int N = 100010;

int n;
int arr[N];
int tmp[N];

void merge_sort(int arr[], int l, int r)
{
    if(l >= r) return;

    int mid = (l + r) >> 1;
    merge_sort(arr, l, mid);
    merge_sort(arr, mid + 1, r);

    int k = 0;
    int i = l;
    int j = mid + 1;
    while(i <= mid && j <= r)
    {
        if(arr[i] < arr[j])
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

    while(i <= mid)
    {
        tmp[k] = arr[i];
        k++;
        i++;
    }
    while(j <= r)
    {
        tmp[k] = arr[j];
        k++;
        j++;
    }

    for(int i = l, j = 0; j < k; i++, j++)
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