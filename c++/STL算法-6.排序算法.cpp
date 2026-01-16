//  STL 算法

// 排序算法

// next_permutation: 生成字典序的下一个排列，如果没有下一个排列则返回 false。

// vector<int> vec = {1, 2, 3};
// do 
// {
//     for (int n : vec) cout << n << " ";
//     cout << endl;
// }
// while (next_permutation(vec.begin(), vec.end()));


// prev_permutation: 生成字典序的上一个排列。

// prev_permutation(vec.begin(), vec.end());
// 用法同上：next_permutation

#include<iostream>
#include<vector>

#include<algorithm>
using namespace std;
int main()
{
    vector<int> vec = {1, 2, 3, 4};
    do 
    {
        for (int n : vec) cout << n << " ";
        cout << endl;
    }
    while (next_permutation(vec.begin(), vec.end()));



    return 0;
}