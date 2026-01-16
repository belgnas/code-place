//数据类型：布尔类型bool(1个字节)

//作用：布尔数据类型代表真或假的值
//0代表假，除此之外非0的数字都代表真，其他字符则不会改变其原来的值

#include<bits/stdc++.h>
using namespace std;

int main()
{
    // ASCII 
    int num = 'a';

    // int a[26];
    // 对每一个字母都减去'a' 
    /*
    'a' => 0
    'b' => 1
    'z' - 'a' => 25
    */
   int a[26] = {0};
   char c;
   cin >> c;
   a[c - 'a']++;

   for (int i = 0; i < 26; i++)
   {
        if (a[i] > 0)
        {
            cout << 'a' + i << ':' << i << endl;
        }
   }
   return 0;
}