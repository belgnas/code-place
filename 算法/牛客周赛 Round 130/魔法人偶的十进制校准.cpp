#include <iostream>
using namespace std;
int main() {

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;

        if (b == 9) {
            if (a % 2 == 0) {
                cout << 1 << " " << 11 << endl;
            }
            else {
                cout << 10 << " " << 11 << endl;
            }
        }
        else if (b == 0) {
            if (a % 2 == 0) {
                cout << 10 << " " << 11 << endl;
            }
            else {
                cout << 1 << " " << 11 << endl;
            }
        }
        else {
            if (b % 3 == 0) {
                cout << b / 3 << " " << 3 << endl;
            }
            else {
                cout << b << " " << 9 << endl;
            }
        }
    }

    return 0;
}