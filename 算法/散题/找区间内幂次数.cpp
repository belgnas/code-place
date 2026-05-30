#include<iostream>
#include<cmath>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        int l, r, k;
        cin >> l >> r >> k;
        bool found = false;
        for (int i = 0; ; i++) {
            int num = static_cast<int>(pow(k, i));
            if (num >= l && num <= r) {
                cout << num << " ";
                found = true;
            } else if (num > r) {
                break;
            }
        }
        if (!found) {
            cout << "None.";
        }
        cout << endl;
    }
    system("pause");
    return 0;
}