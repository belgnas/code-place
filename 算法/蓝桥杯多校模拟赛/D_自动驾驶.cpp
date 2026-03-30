#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    unordered_map<string, int> ump;
    for (int i = 0; i + k <= n; i++) {
        string temp = s.substr(i, k);
        ump[temp] ++;
    }
    
    int ans = 0;
    for (auto a : ump) {
        if (a.second >= 2) {
            ans ++;
        }
    }
    
    cout << ans << endl;
    
    
    return 0;
}