#include <iostream>
#include <algorithm>
using namespace std;

bool test(int a, int b, int c, int d) {
    int temp[4];
    temp[0] = a;
    temp[1] = b;
    temp[2] = c;
    temp[3] = d;
    sort(temp, temp + 4);
    bool temp1234 = true;
    for (int i = 0; i < 4; i++) {
        if (temp[i] != i + 1) {
            temp1234 = false;
            break;
        }
    }
    return temp1234;
}

int main() {

    int t;
    cin >> t;
    while (t-- > 0) {
        int arr[4][4];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                cin >> arr[i][j];
            }
        }

        bool flat = true;

        if (flat == true) {
            for (int i = 0; i < 4; i++) {
                if (test(arr[i][0], arr[i][1], arr[i][2], arr[i][3]) == false) {
                    flat == false;
                    break;
                }
            }
        }

        if (flat == true) {
            for (int j = 0; j < 4; j++) {
                if (test(arr[0][j], arr[1][j], arr[2][j], arr[3][j]) == false) {
                    flat == false;
                    break;
                }
            }
        }

        if (flat == true) {
            for (int i = 0; i < 4; i += 2) {
                for (int j = 0; j < 4; j += 2) {
                    if (test(arr[i][j], arr[i + 1][j], arr[i][j + 1], arr[i + 1][j + 1]) == false) {
                        flat = false;
                        break;
                    }
                }
                if (flat == false) {
                    break;
                }
            }
        }
        
        if (flat == true) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }

    return 0;
}