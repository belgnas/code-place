#include <iostream>
#include <string>
#include <cmath>
using namespace std;

string add1(string n, int begin) {
    bool jingwei = true;
    for (int i = begin; i >= 0; i--) {
        if (i == begin) {
            n[i] = '0';
            continue;
        }

        if (jingwei == true) {
            if (n[i] == '9') {
                n[i] = '0';
            }
            else {
                jingwei = false;
                n[i] += 1;
            }
        }
    }
    for (int i = begin; i < n.size(); i++) {
        n[i] = '0';
    }

    if (jingwei == true) {
        n = "1" + n;
    }
    // cout << "n = " << n << endl;

    return n;
}

int main() {

    int t;
    cin >> t;
    while (t--) {
        string n;
        cin >> n;
        string ans = n;
        bool flat = false;
        for (int i = 0; i < n.size(); i++) {
            if (n[i] >= '5' && n[i] <= '9') {
                flat == true;
                ans = add1(n, i);
                break;
            }
        }
        
        if (flat == false) {
            ans[ans.size() - 1] = '0';
        }

        cout << ans << endl;
    }

}