#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 计算模式串的next数组
void GetNext(string &match, vector<int> &next)
{
    next[0] = 0; // 初始化第一个字符的next值为0
    int i = 1;   // 模式串索引，从第二个字符开始
    int len = match.length();
    int j = i - 1; // j指向当前字符的前一个字符的next位置
    while (i < len)
    {
        // 当前字符与前缀字符匹配
        if (match[i] == match[next[j]])
        {
            next[i] = next[j] + 1; // 更新next值
            i++;
            j = i - 1;
        }
        else if (next[j] == 0)
        { // 无前缀可回退，当前字符next值为0
            next[i] = 0;
            i++;
            j = i - 1;
        }
        else
        { // 回退到next[j]-1位置继续匹配
            j = next[j] - 1;
        }
    }
}

// KMP匹配算法，返回模式串在主串中第一次出现的起始下标（下标从0开始）
int KMP(string &src, string &match)
{
    int len1 = src.length();   // 主串长度
    int len2 = match.length(); // 模式串长度
    if (len1 == 0 || len2 == 0)
        return -1; // 空串处理

    vector<int> next(len2); // 存储模式串的next数组
    GetNext(match, next);   // 预处理next数组

    int i = 0; // 主串索引
    int j = 0; // 模式串索引
    while (i < len1 && j < len2)
    {
        if (src[i] == match[j])
        { // 字符匹配，双指针后移
            i++;
            j++;
        }
        else
        {
            if (j == 0)
            { // 模式串第一个字符不匹配，主串后移
                i++;
            }
            else
            { // 利用next数组回退模式串指针
                j = next[j - 1];
            }
        }
    }

    if (j == len2)
    {                 // 模式串完全匹配
        return i - j; // 返回起始下标
    }
    else
    {
        return -1; // 未匹配
    }
}

int main()
{
    string src, match;
    cout << "请输入主串: ";
    cin >> src;
    cout << "请输入模式串: ";
    cin >> match;

    int result = KMP(src, match);
    if (result != -1)
    {
        cout << "模式串在主串中第一次出现的起始下标为: " << result << endl;
    }
    else
    {
        cout << "模式串未在主串中找到。" << endl;
    }

    return 0;
}