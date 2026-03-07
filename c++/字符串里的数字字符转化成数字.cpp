//字符串里的数字字符转化成整数
//本质上是用是两者的ASCII编码相减来得到的数字

#include<iostream>
#include<string>
using namespace std;

int main()
{
    string ar = "2024/10/06";
    int year,month,day;
    year = int(ar[0]-'0')*1000 + int(ar[1]-'0')*100 + int(ar[2]-'0')*10 + int(ar[3]-'0');//本质上是用是数字字符和0字符的ASCII编码相减来得到的数字
    month = int(ar[5]-'0')*10 + int(ar[6]-'0');
    day = int(ar[8]-'0')*10 + int(ar[9]-'0');
    cout << year << "//" << month << "//" << day << endl;

    system("pause");

    return 0;
}