#include<iostream>
using namespace std;

int main()
{
    int arr[10];
    for (int i = 0; i < 10; i++)
    {
        cin >> arr[i];
    }
    int a = 0;
    int b = 0;
    for (int j = 0; j < 10; j++)
    {
        if (arr[j] >0)
        {
            a++;
        }
        if (arr[j] <0)
        {
            b++;
        }
    }
    cout << "positive:" << a << endl;
    cout << "negative:" << b << endl;
    
    
    
    system("pause");

    return 0;   
}