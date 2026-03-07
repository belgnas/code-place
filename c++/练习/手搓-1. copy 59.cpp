#include <iostream>
using namespace std;
int num[19] = {10000, 36, 720, 360, 80, 252, 108, 72, 54, 180, 72, 180, 119, 36, 306, 1080, 144, 1800, 3600};

int main()
{
    int a[3][3]; // 3*3
    int b[10] = {0};
    int tempi, tempj; // 0 时 对应的位置
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> a[i][j];
            if (a[i][j] == 0) // 这个位置上的数字初始时就能看见了
            {
                tempi = i;
                tempj = j;
            }
            b[a[i][j]]++;
        }
    }

    for (int i = 1; i < 10; i++)
    {
        if (b[i] == 0)
        {
            a[tempi][tempj] = i;
        }
    }
    int sum = 0;
    int a1 = 0, b1 = 0;
    
    for (int i = 0; i < 3; i++)
    {
        cin >> a1 >> b1;
        cout << a[a1 - 1][b1 - 1] << endl;
    }
    int xuanze;
    cin >> xuanze;
    switch (xuanze)
    {
    case 1:
        sum = a[0][0] + a[0][1] + a[0][2];
        break;
    case 2:
        sum = a[1][0] + a[1][1] + a[1][2];
        break;
    case 3:
        sum = a[2][0] + a[2][1] + a[2][2];
        break;
    case 4:
        sum = a[0][0] + a[1][0] + a[2][0];
        break;
    case 5:
        sum = a[0][1] + a[1][1] + a[2][1];
        break;
    case 6:
        sum = a[0][2] + a[1][2] + a[2][2];
        break;
    case 7:
        sum = a[0][0] + a[1][1] + a[2][2];
        break;
    case 8:
        sum = a[0][2] + a[1][1] + a[2][0];
        break;
    }
    cout << num[sum - 6];
    return 0;
}
