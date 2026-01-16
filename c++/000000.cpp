#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main()
{
    // p1：控制字符类型/大小写（1：原类型；2：字母转大写；3：替换为*）
    // p2：控制字符重复次数
    // p3：控制字符生成顺序（1：正序；2：逆序）
    int p1, p2, p3;
    cin >> p1 >> p2 >> p3;
    string ar; // 输入的原始字符串
    cin >> ar;
     
    vector<char> answer; // 存储处理后的字符序列
     
    // 遍历原始字符串的每个字符
    for(int i = 0; i < ar.length(); i++)
    {
        answer.push_back(ar[i]); // 先将当前字符加入结果集
        // 识别有效的连字符区间：当前字符是'-'，且不是首尾字符，且前后字符可形成递增区间
        if(ar[i] == '-' && i > 0 && i < ar.length() - 1)
        {
            answer.pop_back(); // 移除刚才加入的'-'，后续生成区间内的字符
            int begin = int(ar[i - 1]); // 区间起始字符的ASCII码
            int end = int(ar[i + 1]);   // 区间结束字符的ASCII码
            // 若起始字符≥结束字符，说明是无效区间（如"5-3"），保留原'-'
            if(begin >= end)
            {
                answer.push_back(ar[i]);
                continue;
            }
             
            // 处理p1参数的逻辑
            if(p1 != 3)
            {
                // 若区间是字母区间（前后都是字母）
                if(begin >= int('a') && begin <= int('z') && end >= int('a') && end <= int('z'))
                {
                    if(p1 == 2) // p1=2时，字母转大写（ASCII码减32）
                    {
                        begin -= 32;
                        end -= 32;
                    }
                    // p1=1时保持原字母类型，无需处理
                }
                else 
                {
                    // 若区间是数字区间（前后都是数字），则p1=1或2不影响，直接跳过；否则视为无效区间，保留原'-'
                    if(!(begin >= int('0') && begin <= int('9') && end >= int('0') && end <= int('9')))
                    {
                        answer.push_back(ar[i]);
                        continue;
                    }
                }
                // 处理p3参数的顺序逻辑
                if(p3 == 1) // p3=1：正序生成区间内字符
                {
                    for(int j = begin + 1; j <= end - 1; j++)
                    {
                        for(int k = 0; k < p2; k++) // 每个字符重复p2次
                        {
                            answer.push_back(char(j));
                        }
                    }
                }
                else // p3=2：逆序生成区间内字符
                {
                    for(int j = end - 1; j >= begin + 1; j--)
                    {
                        for(int k = 0; k < p2; k++) // 每个字符重复p2次
                        {
                            answer.push_back(char(j));
                        }
                    }
                }
            }
            else // p1=3：区间内字符全部替换为'*'
            {
                for(int j = begin + 1; j <= end - 1; j++)
                {
                    for(int k = 0; k < p2; k++) // 每个*重复p2次
                    {
                        answer.push_back('*');
                    }
                }
            }
        }
    }
     
    // 输出最终处理后的字符序列
    for(int i = 0; i < answer.size(); i++)
    {
        cout << answer[i];
    }
    cout << endl;
     
    return 0;
}