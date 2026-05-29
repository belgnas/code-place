#include <iostream>
#include <vector>
using namespace std;

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

#define int long long

signed main(){

    IOS;

    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> vec(3 * n, 0);
        // 1 2 3 4 5 6 7 8 9
        // 1 4 5
        // 2 6 7
        // 3 8 9
        int num1 = 1;
        int num2 = n + 1;
        for (int i = 0; i < 3 * n; i++){
            if (i % 3 == 0){
                vec[i] = num1;
                num1++;
            }
            else {
                vec[i] = num2;
                num2++;
            }
        }

        for (int i = 0; i < 3 * n; i++){
            cout << vec[i] << " ";
        }
        cout << endl;
    }

    return 0;
}