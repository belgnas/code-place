#include <iostream>
#include <string>
using namespace std;

#define int long long
#define endl '\n'

#define IOS ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

signed main()
{
    IOS;
    
    int t;
    cin >> t;
    while(t--) {
        int k, x, y;
        cin >> k >> x >> y;

        if (k == 1) {
            cout << x + y << endl;
            continue;
        }
        if (k == 2) {
            cout << x / 2 + y << endl;
            continue;
        }

        int ans = 0;
        if (k % 2 == 0) {
            int need_y = k / 2;
            ans += y / need_y;
            y %= need_y;

            ans += x / k;
            x %= k;
        }
        else {
            int need_x = 1;
            int need_y = k / 2;
            int lun = min(x / need_x, y / need_y);
            ans += lun;
            x -= lun * need_x;
            y -= lun * need_y;

            // 剩下的x
            ans += x / k;
            x %= k;

            // 剩下的y
            int per = (k + 1) / 2;
            ans += y / per;
            y %= per;
        }

        if (x + y * 2 >= k) {
            ans++;
        }

        // // 每满k就释放一次大招，充能有2种方式，x和y
        // // 优先使用y，y可以充能2点
        // int ans = 0;
        // // 同时使用x和y
        // if (x > 0 && y > 0) {
        //     int need_y = k / 2;
        //     int need_x = k % 2;

        //     int max_x = 1e18;

        //     if (need_x != 0) {
        //         max_x = x / need_x;
        //     }
            
        //     int max_y = y / need_y;

        //     int lun = min(max_x, max_y);
        //     ans += lun;

        //     x -= lun * need_x;
        //     y -= lun * need_y;
        // }
        

        // if (x > 0) {
        //     int num = x / k;
        //     ans += num;
        //     x %= k;
        // }
        // if (y > 0) {
        //     int temp = (k + 1) / 2;
        //     ans += y / temp;
        //     y %= temp;
        // }

        // if (x + y * 2 >= k) {
        //     ans += 1;
        // }

        cout << ans << endl;




        // // // 如果是x先用完，还有y可以充能
        // // if (y / need_y >= x / need_x) {
        // //     int lun = x / need_x; // 用了几轮
        // //     x %= need_x;
        // //     y -= lun * need_y;
        // //     ans += lun;
        // // }
        // // else {
        // //     int lun = y / need_y; // 用了几轮
        // //     y %= need_y;
        // //     x -= lun * need_x;
        // // }
    }

    return 0;
}