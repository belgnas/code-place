// P8647 [蓝桥杯 2017 省 AB] 分巧克力

#include<iostream>

using namespace std;

int arr[100010][2];
int N, K;

int test(int x)
{
    int ans = 0;
    for(int i = 0; i < N; i++)
    {
        ans += (arr[i][0] / x)*(arr[i][1] / x);
    }
    // if(ans >= K) return true;
    // else return false;
    return ans>=K;
}

int main()
{
    
    cin >> N >> K;
    
    
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            cin >> arr[i][j];
        }
    }
    // int *p = arr;

    int start = 1;
    int end = 100000;
    while(start < end)
    {
        int mid = (start + end + 1) >> 1;//相当于除以2四舍五入
        if(test(mid)) start = mid;
        else end = mid - 1;

    }
    
    cout << start;
    
    // for(int i = 0; i < N; i++)
    // {
    //     for(int j = 0; j < N; j++)
    //     {
    //         cout << arr[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}