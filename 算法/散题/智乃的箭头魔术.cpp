

#include <iostream>
#include <string>
using namespace std;
int main() {
    
    // cout << "000000020002000020000200002100000000000211000000202100000200000021100200000200" << endl;
    
    string s;
    cin >> s;
    char temp = '0';
    string ans = "";
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '0') {
            // cout << "喵0";
            if (temp == '0') temp = '3';
            else if (temp == '1') temp = '2';
            else if (temp == '2') temp = '1';
            else if (temp == '3') temp = '0';
        }
        if (s[i] == '1') {
            // cout << "喵1";
            if (temp == '0') continue;
            else if (temp == '1') temp = '3';
            else if (temp == '2') continue;
            else if (temp == '3') temp = '1';
        }
        if (s[i] == '2') {
            // cout << "喵2";
            if (temp == '0') temp = '1';
            else if (temp == '1') temp = '0';
            else if (temp == '2') temp = '3';
            else if (temp == '3') temp = '2';
        }
        if (s[i] == '3') {
            // cout << "喵3";
            if (temp == '0') temp = '2';
            else if (temp == '1') continue;
            else if (temp == '2') temp = '0';
            else if (temp == '3') continue;
        }
        if (s[i] == '4') {
            // cout << "喵4";
            if (temp == '0') temp = '1';
            else if (temp == '1') temp = '2';
            else if (temp == '2') temp = '3';
            else if (temp == '3') temp = '0';
        }
        if (s[i] == '5') {
            // cout << "喵5";
            if (temp == '0') temp = '3';
            else if (temp == '1') temp = '0';
            else if (temp == '2') temp = '1';
            else if (temp == '3') temp = '2';
        }
        
        ans += temp;

        // cout << temp;
    }
    
    cout << ans << endl;
    
    return 0; 
}