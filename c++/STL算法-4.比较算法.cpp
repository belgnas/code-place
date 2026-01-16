//  STL 算法

//4. 比较算法
// 函数：equal
// 定义：比较两个容器或两个范围内的元素是否相等。
// 语法：
// bool result = equal(first1, last1, first2);
//   或
// bool result = equal(first1, last1, first2, compare_function);

#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v2 = {1, 2, 3, 4, 5};

    bool are_equal = equal(v1.begin(), v1.end(), v2.begin());
    cout << (are_equal ? "Vectors are equal." : "Vectors are not equal.") << endl;

    return 0;
}