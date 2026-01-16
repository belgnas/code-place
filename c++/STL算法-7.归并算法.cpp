// STL 算法

// 归并算法

// merge: 将两个有序区间合并到一个有序区间。

// vector<int> vec1 = {1, 3, 5};
// vector<int> vec2 = {2, 4, 6};
// vector<int> result(6);
// merge(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), result.begin());


// inplace_merge: 在单个区间中合并两个有序子区间。

// inplace_merge(vec.begin(), middle, vec.end());

#include<iostream>
#include<vector>

#include<algorithm>
using namespace std;
int main()
{
    // merge
    vector<int> vec1 = {1, 3, 5};
    vector<int> vec2 = {4, 5, 6};

    vector<int> result(6);

    merge(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), result.begin());

    for(int n : result)
    {
        cout << n << " ";
    }
    cout << endl;

    return 0;
}