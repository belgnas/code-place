#include <iostream>
#include <vector>
using namespace std;
int main() {

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> vec(n, 0);
        bool has_1 = false;
        bool has_67 = false;
        for (int i = 0; i < n; i++) {
            cin >> vec[i];
            if (vec[i] == 1) has_1 = true;
            if (vec[i] == 67) has_67 = true;
        }

        if (has_67) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }

    }

    return 0;
}