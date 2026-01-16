//  STL 算法

// find：顺序查找
// find(v.begin(), v.end(), value)，其中 value 为需要查找的值。
// 如果找到，it 将指向第一个匹配的元素；如果没有找到，it 将等于 numble.end()。
// ps ：这里的 numble.end() 是numble数组末尾的下一个位置  所以不要解引用*it;


// binary_search: 对有序区间进行二分查找。
// 用法和 find 相同

// find_if: 查找第一个满足特定条件的元素。
// 用法暂不用了解
#include<iostream>
#include<vector>

#include<algorithm>
using namespace std;
int main()
{
    //find：顺序查找
    vector<int> numble = {1, 2, 3, 4, 5};
    auto it_1 = find(numble.begin(), numble.end(), 3); // 找得到
    cout << "找到的返回值: " << *it_1 << endl;
    auto it_2 = find(numble.begin(), numble.end(), 100); // 找不到
    if (it_2 != numble.end()) 
        cout << "找到的返回值: " << *it_2 << endl;
    else 
        cout << "元素未找到" << endl;


    // binary_search: 对有序区间进行二分查找。
    vector<int> numble_2 = {1, 3, 1, 4, 7, 6, 7};
    sort(numble_2.begin(), numble_2.end());  // 先排序
    bool it_3 = binary_search(numble_2.begin(), numble_2.end(), 4);
    if (it_3) 
        cout << "找到的返回值 " << endl;
    else 
        cout << "元素未找到" << endl;

    // find_if: 查找第一个满足特定条件的元素。
// 这个暂时还不会用
    // vector<int> vec = {1, 2, 4, 3, 5};

    // auto it_4 = find_if(vec.begin(), vec.end(), [](int x) { return x > 3; });

    // if (it_4!= vec.end())
    //     cout << "找到满足条件的元素: " << *it_4 << endl;
    // else
    //     cout << "未找到满足条件的元素" << endl;



    return 0;
}