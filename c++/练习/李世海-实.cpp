#include<iostream>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        int arr[2][n];

        for(int i = 0; i < n; i++)
        {
            cin >> arr[0][i];
        }
        for(int i = 0; i < n; i++)
        {
            cin >> arr[1][i];
        }
        bool flat_1 = true;
        bool num1_1 = false, num1_2 = false, num1_3 = false;
        int n1, n2, num_n1 = 0, num_n2 = 0;
        for(int i = 0; i < n; i++)
        {
            if(!num1_1 && !num1_2)
            {
                n1 = arr[0][i];
                num1_1 = true;
                num_n1++;
            }
            if(!num1_2 && arr[0][i] != n1)
            {
                n2 = arr[0][i];
                num1_2 = true;
                num_n2++;
            }
            if(num1_1 && arr[0][i] == n1)
            {
                num_n1++;
            }
            if(num1_2 && arr[0][i] == n2)
            {
                num_n2++;
            }
            if(num1_2 && num1_1 && !num1_3 && arr[0][i] != n1 && arr[0][i] != n2)
            {
                num1_3 = true;
            }
        }
        if(!num1_1 || !num1_2 || !num1_3)
        {
            flat_1 = false;
        }
        bool flat_2 = false;
        int num_2 = arr[1][0];
        for(int i = 0; i < n; i++)
        {
            if(num_2 != arr[1][i])
            {
                flat_2 = true;
            }
        }

        if(!flat_1 && flat_2) cout << "NO" << endl;
        else cout << "YES" << endl;
    }

    return 0;
}