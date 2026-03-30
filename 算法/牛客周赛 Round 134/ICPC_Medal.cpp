#include <iostream>
using namespace std;
int main() {
    
    int a, b, c, x, y;
    cin >> a >> b >> c >> x >> y;
    
    while (c >= x || b >= y) {
        if (c >= x) {
            b += (c / x);
            c %= x;
        }
        if (b >= y) {
            a += (b / y);
            c += (b / y);
            b %= y;
        }
        // cout << a << " " << b << " " << c << endl;
    }
    
    cout << a << endl;
    
    return 0;
}