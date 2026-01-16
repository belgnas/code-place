// 牛客竞赛 好串

// 知识点：字符串

// https://ac.nowcoder.com/acm/contest/22669/C

#include<iostream>
#include<string>
using namespace std;
int main()
{
    string str;
    cin >> str;
    
    bool flat = true;
    
    if(str == "")
    {
        flat = false;
    }
    
    int num = 0;
    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] == 'a')
        {
            num ++;
        }
        else
        {
            num --;
        }
        if(num < 0)
        {
            flat = false;
        }
    }
    if(num != 0)
    {
        flat = false;
    }
    
    cout << (flat ? "Good" : "Bad") << endl;
    
    return 0;
}