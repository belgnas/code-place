//  STL 算法

// sort：排序
// sort(v.begin(), v.end(), cmp) 或 sort(a + begin, a + end, cmp)
// 其中 end 是排序的数组最后一个元素的后一位，cmp 为自定义的比较函数。

//从大到小排序
//sort(arr, arr + n, greater<int>())

//从小到大排序
//sort(arr, arr + n, less<int>())

/*没有的话 默认是 less 从小到大*/

// stable_sort：稳定排序，用法同 sort()。

#include<iostream>
#include<vector>

#include<algorithm>
using namespace std;
int main()
{
    // 定义
    vector<int> numble = {5, 3, 6, 8, 5, 1};
    // 排序
    sort(numble.begin(), numble.end());

    // 打印
    for(int num : numble)
    {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}