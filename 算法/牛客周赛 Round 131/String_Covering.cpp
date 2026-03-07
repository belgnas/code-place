#include <iostream>
#include <string>
using namespace std;
int main() {
     
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
         
        bool flat = true;
        s = "0" + s + "0";
        for (int i = 1; i <= s.size() - 2; i++) {
            if (s[i - 1] == '0' && s[i] == '1' && s[i + 1] == '0') {
                flat = false;
                break;
            }
        }
        if (flat) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }
     
    return 0;
}