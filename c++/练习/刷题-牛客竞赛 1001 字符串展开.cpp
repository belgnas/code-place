// 牛客竞赛 1001 字符串展开

// 知识点：模拟

// https://ac.nowcoder.com/acm/contest/20960/1001

#include<iostream>
#include<string>
#include<vector>
using namespace std;
int main()
{
    int p1, p2, p3;
    cin >> p1 >> p2 >> p3;
    string ar;
    cin >> ar;
    
    vector<char> ar_2;
    
    for(int i = 0; i < ar.length(); i++)
    {
        ar_2.push_back(ar[i]);
        if(ar[i] == '-' && i > 0 && i < ar.length() - 1)
        {
            ar_2.pop_back();
            int begin = int(ar[i - 1]);
            int end = int(ar[i + 1]);
            if(begin >= end)
            {
                ar_2.push_back(ar[i]);
                continue;
            }
            
            if(p1 != 3)
            {
                if(begin >= int('a') && begin <= int('z') && end >= int('a') && end <= int('z'))
                {
                    if(p1 == 1)
                    {
                        // 等于没有
                    }
                    if(p1 == 2)
                    {
                        begin -= 32;
                        end -= 32;
                    }
                }
                else
                {
                    
                    if(begin >= int('0') && begin <= int('9') && end >= int('0') && end <= int('9'))
                    {
                        // 无视
                    }
                    else
                    {
                        // 无视规则
                        ar_2.push_back(ar[i]);
                        continue;
                    }
                    
                    
                }
                if(p3 == 1)
                {
                    for(int i = begin + 1; i <= end - 1; i++)
                    {
                        for(int j = 0; j < p2; j++)
                        {
                            ar_2.push_back(char(i));
                        }
                    }
                }
                else
                {
                    for(int i = end - 1; i >= begin + 1; i--)
                    {
                        for(int j = 0; j < p2; j++)
                        {
                            ar_2.push_back(char(i));
                        }
                    }
                }
            }
            else
            {
                for(int i = begin + 1; i <= end - 1; i++)
                {
                    for(int j = 0; j < p2; j++)
                    {
                        ar_2.push_back('*');
                    }
                }
            }
            
            
        }
    }
    
    for(int i = 0; i < ar_2.size(); i++)
    {
        cout << ar_2[i];
    }
    cout << endl;
    
    
    return 0;
}