#include <iostream>
using namespace std;
int main() {

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        bool flat = false;
        while (n > 0) {
            int num = n % 10;
            n /= 10;
            if (num == 0 || num == 5) {
                flat = true;
                break;
            }
        }
        if (flat) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}