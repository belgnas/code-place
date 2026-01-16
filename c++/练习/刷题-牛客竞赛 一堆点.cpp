// 2025/2/23

// 牛客竞赛-一堆点

// 知识点：归并排序（用也可以快速排序）

// 难度：简单

// https://ac.nowcoder.com/acm/problem/15592

#include<iostream>
using namespace std;

const int N = 100010;

struct Point
{
    int x;
    int y;
    int z;
}points[N];

int n;
Point tmp[N];

int count(Point p)
{
    return p.x * p.x + p.y * p.y + p.z * p.z;
}

bool compare(Point p1, Point p2)
{
    if(count(p1) < count(p2))
    {
        return true;
    }
    else if(count(p1) > count(p2))
    {
        return false;
    }
    else
    {
        if(p1.x < p2.x)
        {
            return true;
        }
        else if(p1.x > p2.x)
        {
            return false;
        }
        else
        {
            if(p1.y < p2.y)
            {
                return true;
            }
            else if(p1.y > p2.y)
            {
                return false;
            }
            else
            {
                if(p1.z < p2.z)
                {
                    return true;
                }
                else if(p1.z > p2.z)
                {
                    return false;
                }
                else return false;
            }
        }
    }
}

void merge_sort(Point arr[], int l, int r)
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
        if(compare(arr[i], arr[j]))
        {
            tmp[k] = arr[i];
            i++;
            k++;
        }
        else
        {
            tmp[k] = arr[j];
            j++;
            k++;
        }
    }
    
    while(i <= mid)
    {
        tmp[k] = arr[i];
        i++;
        k++;
    }
    while(j <= r)
    {
        tmp[k] = arr[j];
        j++;
        k++;
    }
    
    for(int i = l, j = 0; i <= r; i++, j++)
    {
        arr[i] = tmp[j];
    }
}

int main()
{
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++)
    {
        scanf("%d%d%d", &points[i].x, &points[i].y, &points[i].z);
    }
    
    merge_sort(points, 0, n - 1);
    
    for(int i = 0; i < n; i++)
    {
        printf("%d %d %d\n", points[i].x, points[i].y, points[i].z);
    }
    
    return 0;
}