#include <iostream>
#include <string>
using namespace std;

#define int long long

int to_num(string s)
{
    int num = 0;
    for(int i = 1; i < s.size(); i++)
    {
        if (s[i] >= '0' && s[i] <= '9') {
            num = num * 16 + (s[i] - '0');
        }
        else if (s[i] >= 'a' && s[i] <= 'f') {
            num = num * 16 + (s[i] - 'a' + 10);
        }
    }
    return num;
}

string to_str(int num)
{
    string s = "";
    while (num > 0) {
        int x = num % 16;
        if (x >= 0 && x <= 9) {
            s = char(x + '0') + s;
        }
        else {
            s = char(x - 10 + 'a') + s;
        }
        num /= 16;
    }
    while (s.size() < 6) {
        s = "0" + s;
    }
    s = "#" + s;

    return s;
}



signed main()
{

    int t;
    cin >> t;
    while (t--) {
        string s1;
        cin >> s1;
        int num1 = to_num(s1);

        // cout << num1 << endl;

        int num2 = (1LL << 24) - 1 - num1;
        string s2 = to_str(num2);

        cout << s2 << endl;
    }

    return 0;
}
