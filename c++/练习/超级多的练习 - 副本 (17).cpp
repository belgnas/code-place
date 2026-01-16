#include <bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

// DFS 函数，用于尝试所有数字组合，判断是否能得到目标和
bool dfs(vector<int> &arr, int idx, int now, int target)
{
    if (now == target)
        return true;
    
    // 如果当前和超过目标和或者已经遍历完所有数字，返回 false
    if (now > target || idx == arr.size())
        return false;

    // 选择当前数字，继续递归搜索
    bool choose = dfs(arr, idx + 1, now + arr[idx], target);
    // 不选择当前数字，继续递归搜索
    bool not_choose = dfs(arr, idx + 1, now, target);

    // 只要有一种情况能得到目标和，就返回 true
    return choose || not_choose;
}

int main()
{
    IOS;

    string s;
    cin >> s;

    vector<int> arr;
    int sum = 0;

    for (int i = 0; i < s.length(); i++)
    {
        arr.push_back(s[i] - '0');
        sum += arr[i];
    }

    sort(arr.begin(), arr.end()); // 这里其实不需要排序的，因为后面dfs了全部的数字组合

    bool flat = false;

    if (sum % 2 == 1)
    {
        flat = false;
    }
    else
    {
        // 调用 DFS 函数，尝试找到和为总和一半的组合
        flat = dfs(arr, 0, 0, sum / 2);
    }

    if (flat)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}