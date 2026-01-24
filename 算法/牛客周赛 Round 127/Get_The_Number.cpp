#include<iostream>
using namespace std;
signed main() {

    double a, b, c;
    cin >> a >> b >> c;
    if (a + b == c || a - b == c || a * b == c || a / b == c) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }

    return 0;
}