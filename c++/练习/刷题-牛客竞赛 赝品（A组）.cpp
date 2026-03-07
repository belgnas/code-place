// 牛客竞赛 赝品（A组）

// 知识点：数组、哈希、模拟

// 难度：易

// https://ac.nowcoder.com/acm/contest/72647/B

// 思路：思路：建议使用map等哈希容器（java为HashMap，python为dict），这样可以比较方便统计每个元素的次数。另外也可以通过排序等方式来达成目的。

#include<iostream>
#include<map>
#include<vector>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int num;
    map<int, int> m;
    for(int i = 0; i < n; i++)
    {
        cin >> num;
        m[num]++;
    }
    vector<int> arr;
    for(auto i : m)
    {
        if(i.second == 1)
        {
            arr.push_back(i.first);
        }
    }
    
    cout << arr.size() << endl;
    for(int i = 0; i < arr.size() ; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    
    return 0;
}