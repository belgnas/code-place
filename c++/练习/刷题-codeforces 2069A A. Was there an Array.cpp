// 刷题-codeforces 2096A A - Was there an Array?

// 知识点：模拟

// 难度：简单

// https://codeforces.com/contest/2069/problem/A

#include<iostream>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        n -= 2;
        int arr[n];
        for(int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }

        bool flat = true;

        for(int i = 1; i < n - 1; i++)
        {
            if(arr[i] == 0 && arr[i - 1] == 1 && arr[i + 1] == 1)
            {
                flat = false;
            }
        }

        if(flat)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
}