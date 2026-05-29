#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr)

#define int long long

signed main() {
    
    IOS;

    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<vector<int>> a(n, vector<int>(m, 0));

        // k = 1
        // 0 0 0 0 0 0 0
        // 0 1 0 1 0 1 0
        // 0 0 0 0 0 0 0
        // 0 1 0 1 0 1 0
        if (k == 1) {
            for (int i = 0; i < n; i++) {
                if (i % 2 == 0) {
                    for (int j = 0; j < m; j++) {
                        a[i][j] = 0;
                    }
                }
                else {
                    for (int j = 0; j < m; j++) {
                        if (j % 2 == 0) {
                            a[i][j] = 0;
                        }
                        else {
                            a[i][j] = 1;
                        }
                    }
                }
            }
        }

        // k = 2
        // // 0 1 0 1 0 1
        // // 1 0 1 0 1 0
        // // 0 1 0 1 0 1
        // // 1 0 1 0 1 0
        // 0 0 0 0 0 0
        // 1 1 1 1 1 1
        // 0 0 0 0 0 0
        // 1 1 1 1 1 1
        // 或
        // 0 1 0 1 0
        // 0 1 0 1 0
        // 0 1 0 1 0
        // 0 1 0 1 0
        // 0 1 0 1 0
        if (k == 2) {
            // for (int i = 0; i < n; i++) {
            //     if (i % 2 == 0) {
            //         for (int j = 0; j < m; j++) {
            //             if (j % 2 == 0) {
            //                 a[i][j] = 0;
            //             }
            //             else {
            //                 a[i][j] = 1;
            //             }
            //         }
            //     }
            //     else {
            //         for (int j = 0; j < m; j++) {
            //             if (j % 2 == 0) {
            //                 a[i][j] = 1;
            //             }
            //             else {
            //                 a[i][j] = 0;
            //             }
            //         }
            //     }
            // }
            if ((m / 2) * n > (n / 2) * m) {
                for (int i = 0; i < n; i++) {
                    if (i % 2 == 0) {
                        for (int j = 0; j < m; j++) {
                            a[i][j] = 0;
                        }
                    }
                    else {
                        for (int j = 0; j < m; j++) {
                            a[i][j] = 1;
                        }
                    }
                }
            }
            else {
                for (int i = 0; i < m; i++) {
                    if (i % 2 == 0) {
                        for (int j = 0; j < n; j++) {
                            a[j][i] = 0;
                        }
                    }
                    else {
                        for (int j = 0; j < n; j++) {
                            a[j][i] = 1;
                        }
                    }
                }
            }
        }

        // k = 3
        // 0 1 0 1 0 1 0
        // 1 1 1 1 1 1 1
        // 0 1 0 1 0 1 0
        // 1 1 1 1 1 1 1
        if (k == 3) {
            for (int i = 0; i < n; i++) {
                if (i % 2 == 0) {
                    for (int j = 0; j < m; j++) {
                        if (j % 2 == 0) {
                            a[i][j] = 0;
                        }
                        else {
                            a[i][j] = 1;
                        }
                    }
                }
                else {
                    for (int j = 0; j < m; j++) {
                        a[i][j] = 1;
                    }
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << a[i][j] << " ";
            }
            cout << endl;
        }
    }


    return 0;
}