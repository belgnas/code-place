#include<bits/stdc++.h>

using namespace std;

#define IOS ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

bool flat(int arr[9][9])
{
    int tmp[9];
    
    memset(tmp, 0, sizeof tmp);
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            // arr[i][j]--;
            tmp[(arr[i][j])]++;
            if(tmp[(arr[i][j])] == 2)
            {
                return false;
            }
            // arr[i][j]++;
        }
    }

    
    for(int i = 0; i < 9; i++)
    {
        memset(tmp, 0, sizeof tmp);
        for(int j = 0; j < 9; j++)
        {
            // arr[j][i]--;
            tmp[(arr[j][i])]++;
            if(tmp[(arr[j][i])] == 2)
            {
                return false;
            }
            // arr[j][i]++;
        }
    }

    
    for(int i = 0; i < 9; i += 3)
    {
        for(int j = 0; j < 9; j += 3)
        {
            memset(tmp, 0, sizeof tmp);
            for(int k = i; k < i + 3; k++)
            {
                for(int l = j; l < j + 3; l++)
                {
                    // arr[k][l]--;
                    tmp[(arr[k][l])]++;
                    if(tmp[(arr[k][l])] == 2)
                    {
                        return false;
                    }
                    // arr[k][l]++;
                }
            }
            
        }
    }

    return true;
}

int main()
{
    IOS;

    int n;
    cin >> n;

    int arr[9][9];
    while(n--)
    {
        for(int i = 0; i < 9; i++)
            for(int j = 0; j < 9; j++)
                cin >> arr[i][j];

        if(flat(arr))
            cout << "1" << endl;
        else
            cout << "0" << endl;
    }
    
    return 0;
}