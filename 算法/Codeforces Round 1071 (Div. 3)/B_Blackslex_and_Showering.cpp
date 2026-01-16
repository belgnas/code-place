#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> arr(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            cin >> arr[i];
        }

        int sum = 0;
        for (int i = 2; i <= n; i++) {
            sum += abs(arr[i] - arr[i - 1]);
        }
        
        int ans = sum;
        for (int i = 1; i <= n; i++) {
            int temp = sum;
            
            if (i >= 2) temp -= abs(arr[i] - arr[i - 1]);
            if (i <= n - 1) temp -= abs(arr[i] - arr[i + 1]);
            if (i >= 2 && i <= n - 1) temp += abs(arr[i - 1] - arr[i + 1]);

            ans = min(ans, temp);
        }

        cout << ans << endl;
    }

    return 0;
}