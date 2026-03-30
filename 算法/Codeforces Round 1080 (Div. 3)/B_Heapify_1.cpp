#include <iostream>
#include <vector>
using namespace std;

int main() {

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> vec(n + 1, 0);
        for (int i = 1; i <= n; i++) cin >> vec[i];
        // 1 2
        // 2 4
        // 3 6
        // 4 8
        // 5 10
        // 6 12

        // 1 2 4 8 16 32
        // 3 6 12 24 48
        // 5 10 20 40 
        // 7 14 28 56
        // 9 18 36 72
        // 11 22 44
        bool ans = true;
        for (int i = 1; i <= n; i++) {
            if (vec[i] != i) {
                int idx = i;
                bool flat = false;
                while (idx <= n) {
                    if (vec[idx] == i) {
                        flat = true;
                        break;
                    }
                    idx *= 2;
                }
                if (flat) {
                    swap(vec[idx], vec[i]);
                }
                else {
                    ans = false;
                    break;
                }
            }
        }

        if (ans) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }


    return 0;
}