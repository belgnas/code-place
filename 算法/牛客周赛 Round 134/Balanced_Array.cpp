#include <iostream>
#include <vector>
#include <unordered_map> 
using namespace std;

int main() {
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n, 0);
        for (int i = 0; i < n; i++) cin >> a[i];
        
        long long ans = 0;
        unordered_map<int, int> cnt;
        int l = 0;
        for (int r = 0; r < n; r++) {
            cnt[a[r]]++;
            
            while (true) {
                if (cnt.size() > 2) {
                    cnt[a[l]]--;
                    if (cnt[a[l]] == 0) {
                        cnt.erase(a[l]);
                    }
                    l++;
                }
                else {
                    int mx = -1e9;
                    int mn = 1e9;
                    for (auto& p : cnt) {
                        mn = min(mn, p.first);
                        mx = max(mx, p.first);
                    }
                    if (mx - mn > 1) {
                        cnt[a[l]]--;
                        if (cnt[a[l]] == 0) {
                            cnt.erase(a[l]);
                        }
                        l++;
                    }
                    else {
                        break;
                    }
                }
            }
            ans += r - l + 1;
        }
        cout << ans << endl;
        
    }
    
    return 0;
}