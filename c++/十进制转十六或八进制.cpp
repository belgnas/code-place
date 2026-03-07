//头文件#include<iomanip>
//hex<<a
//oct<<b

//dec：10进制
//hex：16进制
//otc： 8进制

//cout << hex << a << endl;   中的hex<<a
//cout << oct << b << endl;   中的oct<<b

#include<iostream>

using namespace std;
int main()
{
    int a,b;
    cin >> a >> b;
    cout << hex << a << endl;// a 的 16进制
    cout << oct << b << endl;// b 的 8进制 

    return 0;
}