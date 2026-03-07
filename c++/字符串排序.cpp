//给字符串排序

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

int main() 
{
    vector<string> arr;
    int n;
    cin >> n;

    // 这行代码用途：清理输入缓冲区的遗留换行符
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string word;
    for(int i = 0; i < n; i++)
    {
        getline(cin, word);
        arr.push_back(word);
    }

    sort(arr.begin(), arr.end()); // 使用 sort 函数对向量 arr 中的字符串按照字典序进行排序

    for(int i = 0; i < static_cast<int>(arr.size()); i++)
    {
        cout << arr[i] << endl;
    }
    
    return 0;
}