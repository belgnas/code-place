//等比数列

//示例：2^n：2、4、8、16、32...
//描述：输入一个整数，输出等比数列2^n第n项的值
#include<iostream>
using namespace std;

int digui(int n)
{
    int numble = 0;
    if(n==1)//注意是“==”
    {
        numble = 2;
    }
    else
    {
        numble = digui(n-1)*2;
    }
    return numble;
}

int main()
{
    int a = 0;
    cin >> a;
    cout << digui(a) << endl;

    system("pause");
    return 0;
}