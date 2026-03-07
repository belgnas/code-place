//  STL 算法

// copy：复制
// copy(起始位置, 结束位置的下一个, 复制到的那个容器的起始位置);

#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int main()
{
    vector<int> source = {1, 2, 3, 4, 5};
    int destination[5];
    copy(source.begin(), source.end(), destination);

    for (int i = 0; i < 5; ++i)
    {
        cout << destination[i] << " ";
    }
    cout << endl;

    return 0;
}