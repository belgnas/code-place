#include<iostream>

using namespace std;

int main()
{
    int T;
    cin >> T;
    int arr[T];
    for(int i=0; i<T; i++)
    {
        cin >> arr[i];
    }
    for(int i=0; i<T; i++)
    {
        //外层循环（多少行）
        for(int j=1; j<=arr[i]; j++)
        {
            //内层循环
            //空格（第i行有多少个）
            for(int k=1; k<=arr[i]-j; k++)
            {
                cout << " ";
            }
            //*字符（第i行有多少个）
            for(int l=1; l<=2*j-1; l++)
            {
                cout << "*";
            }
            cout << endl;
        }
        //外层循环（小倒三角）
        for(int m=arr[i]-1; m>=1; m--)
        {
            //内部循环
            //空格（当前高度为m时空格有多少个）
            for(int n=1; n<=arr[i]-m; n++)
            {
                cout << " ";
            }
            //*字符
            for(int o=1; o<=2*m-1; o++)
            {
                cout << "*";
            }
            cout << endl;
        }
    }

    return 0;
}