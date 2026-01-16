// 组合型枚举

// 从 1~n 这 n 个整数中随机选出 m 个，输出所有可能的选择方案。

#include<iostream>
#include<vector>
using namespace std;

vector<int> vec;

void test(int n, int m, int num)
{
    if(static_cast<int>(vec.size()) == m)
    {
        // 打印
        for(int num : vec)
        {
            cout << num << " ";
        }
        cout << endl;

        // 返回
        return;
    }

    for(int i = num; i <= n; i++)
    {
        vec.push_back(i);
        test(n, m, i + 1);
        vec.pop_back();
    }


}

int main()
{
    int n,m;//1~m个整数选择n个
    cin >> n >> m;
    test(n, m, 1);
    return 0;

    return 0;
}