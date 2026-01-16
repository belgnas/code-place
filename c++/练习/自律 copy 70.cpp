#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 解析输入字符串，将每5位转为一个整数
vector<int> test01(int len, string s)
{
    int n = (len / 5);
    vector<int> arr(n);
    
    for(int i = 0; i < n; i++)
    {
        int num = 0;
        for(int j = 0; j < 5; j++)
        {
            num = num * 10 + (s[i*5 + j] - '0');
        }
        arr[i] = num;
    }
    
    return arr;
}

// 将数字编码转换为对应的3位字符串
vector<string> test02(vector<int> &arr)
{
    int len = arr.size();
    vector<string> ans(len);
    
    for(int i = 0; i < len; i++)
    {
        int code = arr[i];
        
        // 正确的编码转换逻辑
        char c1 = 'a' + code / (26 * 26);
        code %= (26 * 26);
        char c2 = 'a' + code / 26;
        char c3 = 'a' + code % 26;
        
        ans[i] = string(1, c1) + string(1, c2) + string(1, c3);
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int T;
    cin >> T;
    while(T--)
    {
        int len;
        cin >> len;
        string s;
        cin >> s;
        
        vector<int> arr = test01(len, s);
        vector<string> ans = test02(arr);

        for(auto t : ans)
        {
            cout << t;
        }
        cout << endl;
    }
    
    return 0;
}


// #include<bits/stdc++.h>
// using namespace std;
// #define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

// vector<int> test01(int len, string s)
// {
//     int n = (len / 5);
//     vector<int> arr(n);
//     for(int i = 0; i <= 14; i += 5)
//     {
//         int num = 0;
//         int j = 0;
//         while(j <= 4)
//         {
//             num *= 10;
//             num += (s[i + j] - '0');
//             j++;
//         }
//         arr[i / 5] = num;
//     }
    
//     return arr;
// }

// vector<string> test02(vector<int> &arr)
// {
//     int len = arr.size();
//     vector<string> ans(len);
//     for(int i = 0; i < len; i++)
//     {
//         while(arr[i] > 0)
//         {
//             int num = arr[i] % 26;
//             arr[i] /= 26;
//             ans[i] += (num + 'a');
//         }
//         while(ans[i].length() < 3)
//         {
//             ans[i] = 'a' + ans[i];
//         }
//         // cout << "test" << endl;
//         // for(auto t : ans)
//         // {
//         //     cout << t << " ";
//         // }
//         // cout << endl;
//     }

//     return ans;
// }

// int main()
// {
//     IOS;
//     int T;
//     cin >> T;
//     while(T--)
//     {
//         int len;
//         cin >> len;
//         string s;
//         cin >> s;
//         vector<int> arr = test01(len, s);
        
//         // for(auto t : arr)
//         // {
//         //     cout << t << " ";
//         // }
//         // cout << endl;

//         vector<string> ans = test02(arr);

//         for(auto t : ans)
//         {
//             cout << t;
//         }
//         cout << endl;
//     }
    
//     return 0;
// }