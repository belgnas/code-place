#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        string n;
        cin >> n;
        long long max_sum = 0;
        int len = n.length();

        for (int i = 1; i < len; ++i)
        {
            string s1 = n.substr(0, i);
            string s2 = n.substr(i);

            long long num1 = stoll(s1);
            long long num2 = stoll(s2);
            long long current_sum = num1 + num2;

            if (current_sum > max_sum)
            {
                max_sum = current_sum;
            }
        }

        cout << max_sum << endl;
    }
    return 0;
}