#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i * i <= n; i++)
    {
        for (int j = 0; i * i + j * j <= n; j++)
        {
            for (int k = 0; i * i + j * j + k * k <= n; k++)
            {
                int t = n - i * i - j * j - k * k;
                int m = sqrt(t);
                if (m * m == t)
                {
                    cout << i << " " << j << " " << k << " " << m << endl;
                    return 0;
                }
            }
        }
    }
    return 0;
}
