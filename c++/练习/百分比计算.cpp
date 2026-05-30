#include <iostream>

using namespace std;

int main()
{
    double A;
    cin >> A;
    A /= 100.0;
    for (int x, y = 1; y <= 100000; y++)
    {
        x = A * y;
        for (int i = max(x - 10, 0), v; i <= min(x + 10, y); i++)
        {
            v = (double(i) / double(y) * 1e5 + 5) / 10;
            // v /= 1000;
            if (abs(A * 100 - double(v) / 100) == 0)
            {
                cout << y << "\n";
                return 0;
            }
        }
    }
    return 0;
}
