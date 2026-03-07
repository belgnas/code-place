#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<int> stones(N); // 存储每个外星人当前拥有的宝石数量
    for (int i = 0; i < N; i++)
    {
        cin >> stones[i];
    }

    // 模拟N年的过程
    for (int year = 0; year < N; year++)
    {
        int currentAdultIndex = year; // 当前成年的外星人索引，根据条件可知每年正好有一个外星人成年
        // 让其他成年且有宝石的外星人赠送宝石
        for (int j = 0; j < currentAdultIndex; j++)
        {
            if (stones[j] > 0)
            {
                stones[j]--;
                stones[currentAdultIndex]++;
            }
        }
    }

    // 输出每个外星人最终拥有的宝石数量
    for (int i = 0; i < N; i++)
    {
        cout << stones[i] << " ";
    }
    cout << endl;

    return 0;
}