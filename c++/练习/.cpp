#include<iostream>
//#include<algorithm>
using namespace std;
int main()
{
    cout << "软件24-1 李世海";
    int length;
    int n,m,num;
    cin >> length;    
    cin >> n;

    for(int i = 0; i < n; i++)
    {
        cin >> m;
        if(i == 0) num = m;
        int x = length - m;
        num = (m<x?m:x)>num?(m<x?m:x):num;  /*min(m, length - m, num)*/
    }
    
    cout << num;
    
    return 0;
}