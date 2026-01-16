// 链接：https://ac.nowcoder.com/acm/contest/95677/M
// 来源：牛客网

// 题目描述 
// 一个字符串是回文串，当且仅当该字符串从前往后读和从后往前读是?样的，例如aabaa和ccddcc都是回?串， 但abcd不是。 乎乎有 n 个仅包含小写字母的字符串，他想请你编写程序判断每个字符串是否由两个长度至少为 2的回文串前后拼接而成。

// 输入描述:
// 第一行包含?个正整数n，代表字符串数量。
// 之后n行每行?个仅包含小写字母的字符串。

// 输出描述:
// 对于每个字符串输出一行，如果该字符串由两个长度?少为2的回文串前后拼接而成则输出 Yes，否则输出 No。 

// 示例1

// 输入
// 4
// abcd
// aabbb
// aaac
// abcdd

// 输出
// No
// Yes
// No
// No

// 说明
// 对于第 1,3,4个字符串，都不是由两个长度?少为2的回?串前后拼接?成。
// 第2 个字符串由回?串 aa和 bbb前后拼接?成，并且两个回?串长度都?少为2 。 

#include<iostream>
#include<cstring>
using namespace std;
int main()
{
    
    int n;
    cin >> n;
    string word;

    for(int l = 1; l <= n; l++)
    {
        cin >> word;
        bool flat1 = true;
        bool flat2 = true;
        
        //先判断总长度
        if(word.length() < 4) 
        {
            cout << "No" << endl;
            continue;
        }
        
        for(int p = 1; p + 2 <= word.length() - 1; p++)
        {
            //悲：这两行找了好久，悲，找了至少2h
            flat1 = true;
            flat2 = true;
            
            for(int i = 0; i <= p; i++)
            {
                if(word[i] != word[p-i])
                {
                    flat1 = false;
//                     cout << "前半部分有问题：";
                    break;
                }
            }
        
        
            for(int i = p + 1; i <= word.length() - 1; i++)
            {
                if(word[i] != word[p + word.length() - i])
                {
                    flat2 = false;
//                     cout << "后半部分有问题：";
                    break;
                }
            }

        
            if(flat1 && flat2)
            {
//                 cout << "Yes 结束" << "  p = " << p << "  第" << l << "个字符串" << endl;
                cout << "Yes" << endl;
                break;
            }
//              else cout << "No 继续判断" << "  p = " << p << "  第" << l << "个字符串" << endl;
        }
        if(!flat1 || !flat2)
        {
//             cout << "No 结束" << "  第" << l << "个字符串" << endl;
            cout << "No" << endl;
        }
        
        
    }
}