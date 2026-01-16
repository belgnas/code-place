// acwing-6134. 哞叫时间II

// 知识点：枚举

// 难度：中等

// https://www.acwing.com/problem/content/6137/

// 2025蓝桥杯每日一题4

#include<iostream>
#include<cstring>
using namespace std;

#define IOS ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
// 需要在main函数中输入IOS来使用这行代码

const int N = 1000010;

int n;
int arr[N];
int arr_1[N], arr_2[N];
int num_kind[N];
long long ans = 0;


int main()
{
    IOS;
    
    cin >> n;
    
    cin >> arr[0];
    arr_1[arr[0]] = 1;
    num_kind[0] = 1;
    
    
    for(int i = 1; i < n; i++)
    {
        cin >> arr[i];
        num_kind[i] = num_kind[i - 1];
        if(arr_1[arr[i]] == 0) num_kind[i]++;
        arr_1[arr[i]]++;
    }
    
    for(int i = n - 1; i >= 1; i--)
    {
        arr_2[arr[i]]++;
        if(arr_2[arr[i]] == 2)
        {
            ans += num_kind[i - 1];
            // cout << "喵" << num_kind[i] << " " << i << endl;
            if(arr_1[arr[i]] > 2) ans--;
        }
    }
    
    cout << ans << endl;
    
    
    return 0;
}