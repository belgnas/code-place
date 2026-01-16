// #include<iostream>
// #include<algorithm>
// #include<vector>
#include <bits/stdc++.h>
using namespace std;

    const int N = 2e6 + 10;
    // int L[N], R[N];
    vector<int> L(N);
    vector<int> R(N);

int main()
{
    int n, m;
    cin >> n >> m;



    // vector<int> L(200010, 0);
    // vector<int> R(200010, 0);


    int x;
    int num_0;
    for(int i = 1; i <= n; i++)
    {
        cin >> x;
        if(x == 0) num_0++;
        else if(x > 0) R[x]++;
        else if(x < 0) L[-x]++;
    }

// 测试代码
    // for(int i = 5; i >= 1; i--)
    // {
    //     cout << L[i];
    // }
    // cout << " " << num_0 << " ";
    // for(int i = 1; i <= 5; i++)
    // {
    //     cout << R[i];
    // }
    // cout << endl;

    for(int i = 1; i <= m; i++)
    {
        L[i] += L[i - 1];
        R[i] += R[i - 1];

    }

// 测试代码
    // for(int i = 5; i >= 1; i--)
    // {
    //     cout << L[i];
    // }
    // cout << " " << num_0 << " ";
    // for(int i = 1; i <= 5; i++)
    // {
    //     cout << R[i];
    // }
    // cout << endl;

    int answer = 0;
    int sum_1, sum_2;
    for(int i = 1; i <= m; i++)
    {
        //先向左移，在全力向右移
        sum_1 = L[i];
        if(m - i * 2 > 0) sum_1 += R[m - i * 2];
        
        answer = max(answer, sum_1);

        //先向右移，在全力向左移
        sum_2 = R[i];
        if(m - i * 2 > 0) sum_2 += L[m - i * 2];

        answer = max(answer, sum_2);
    }

    cout << answer + num_0 << endl;
    

    return 0;
}