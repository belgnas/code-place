#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    
    string s;
    cin >> s;
    int ans = 0;
    for (int i = 0; i < s.size(); i++) {
        int num = s[i] - '0';
        ans *= 10;
        ans += num;
    }
    cout << ans << endl;
    
    return 0;
}