// AcWing 6098. 局部最小值

// 知识点：枚举

// 难度：简单

// https://www.acwing.com/problem/content/6101/

#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
    int n;
    int r, l;
    cin >> n >> l >> r;
    
    vector<int>arr;
    int num;
    bool flat = false;
    for(int i = 0; i < n; i++)
    {
        cin >> num;
        if(i + 1 == l) flat = true;
        if(i + 1 == r)
        {
            arr.push_back(num);
            flat = false;
        }
        
        if(flat) arr.push_back(num);
    }
    
    cout << *min_element(arr.begin(), arr.end()) << endl;
    
    return 0;
}