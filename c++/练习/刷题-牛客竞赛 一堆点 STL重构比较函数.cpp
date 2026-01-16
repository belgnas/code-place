// 2025/2/23

// 牛客竞赛-一堆点

// 知识点：归并排序（用也可以**快速排序-自定义比较函数）

// 难度：简单

// https://ac.nowcoder.com/acm/problem/15592

#include<iostream>
#include<algorithm>
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

bool compare(Point p1, Point p2) // 把要排在前边成立的条件的返回值定为true
{
    // if(count(p1) < count(p2))
    // {
    //     return true;
    // }
    // else if(count(p1) > count(p2))
    // {
    //     return false;
    // }
    // else
    // {
    //     if(p1.x < p2.x)
    //     {
    //         return true;
    //     }
    //     else if(p1.x > p2.x)
    //     {
    //         return false;
    //     }
    //     else
    //     {
    //         if(p1.y < p2.y)
    //         {
    //             return true;
    //         }
    //         else if(p1.y > p2.y)
    //         {
    //             return false;
    //         }
    //         else
    //         {
    //             if(p1.z < p2.z)
    //             {
    //                 return true;
    //             }
    //             else if(p1.z > p2.z)
    //             {
    //                 return false;
    //             }
    //             else return false;
    //         }
    //     }
    // }

    // 或

    if(count(p1) != count(p2))
    {
        return count(p1) < count(p2); // 从小到大就是 小于(<)
    }
    else
    {
        if(p1.x != p2.x)
        {
            return p1.x < p2.x;
        }
        else
        {
            if(p1.y != p2.y)
            {
                return p1.y < p2.y;
            }
            else
            {
                return p1.z < p2.z;
            }
        }
    }
}

int main()
{
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++)
    {
        scanf("%d%d%d", &points[i].x, &points[i].y, &points[i].z);
    }
    
    sort(points, points + n, compare);
    
    for(int i = 0; i < n; i++)
    {
        printf("%d %d %d\n", points[i].x, points[i].y, points[i].z);
    }
    
    return 0;
}