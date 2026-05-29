// #include <iostream>
// #include <string>
// #include <vector>
// #include <algorithm>
// using namespace std;

// #define int long long

// struct Str{
//     string s;
//     vector<int> num;
// };

// bool compare(Str &a, Str &b) {
//     if (a.num.empty()) {
//         vector<int> temp(26, 0);
//         for (int j = 0; j < a.s.size(); j++) {
//             temp[a.s[j] - 'a']++;
//         }
//         a.num = temp;
//     }
//     if (b.num.empty()) {
//         vector<int> temp(26, 0);
//         for (int j = 0; j < b.s.size(); j++) {
//             temp[b.s[j] - 'a']++;
//         }
//         b.num = temp;
//     }

//     bool flat = false;
//     for (int i = 0; i < a.num.size(); i++) {
//         if (a.num[i] == b.num[i]) continue;
//         else {
//             return a.num[i] > b.num[i];
//             break;
//         }
//     }
//     return a.s < b.s;
// }

// signed main() {

//     int n;
//     cin >> n;
//     vector<Str> vec(n);
//     for (int i = 0; i < n; i++) {
//         cin >> vec[i].s;
//     }

//     sort(vec.begin(), vec.end(), compare);

//     for (int i = 0; i < n; i++) {
//         cout << vec[i].s << " ";
//     }
//     cout << endl;

//     return 0;
// }


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define int long long

bool compare(string a, string b) {
    vector<int> num1(26, 0);
    for (int j = 0; j < a.size(); j++) {
        num1[a[j] - 'a']++;
    }
    vector<int> num2(26, 0);
    for (int j = 0; j < b.size(); j++) {
        num2[b[j] - 'a']++;
    }

    bool flat = false;
    for (int i = 0; i < num1.size(); i++) {
        if (num1[i] == num2[i]) continue;
        else {
            return num1[i] > num2[i];
        }
    }
    
    return a < b;
}

signed main() {

    int n;
    cin >> n;
    vector<string> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }

    sort(vec.begin(), vec.end(), compare);

    for (int i = 0; i < n; i++) {
        cout << vec[i] << " ";
    }
    cout << endl;

    return 0;
}