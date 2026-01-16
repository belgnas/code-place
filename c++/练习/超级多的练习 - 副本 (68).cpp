#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 50010;

int n;
string s[N];

int main()
{
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++)
        getline(cin, s[i]);

    sort(s, s + n);

    string now = "00:00:00", end = "23:59:59";
    for (int i = 0; i < n; i++)
    {
        if (now < s[i].substr(0, 8)) // 若开始时间大于now，则说明有空闲
            cout << now << " - " << s[i].substr(0, 8) << endl;
        now = s[i].substr(11, 8); // 更新当前时间
    }

    if (now < end)
        cout << now << " - " << end << endl;

    return 0;
}
