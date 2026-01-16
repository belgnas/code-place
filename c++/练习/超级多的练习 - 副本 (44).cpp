#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    int n;
    string str[22];
    string s = "qiao ben zhong.";
    string t = "Skipped";
    cin >> n;
    getchar(); // 读掉输入n后的换行符
    for (int i = 0; i < n; i++)
    {
        getline(cin, str[i]);
        if (str[i].find("ong,") != string ::npos)
        {
            if (str[i].rfind("ong.") != string ::npos)
            {
                int k = 0, f = 0;
                unsigned int j = str[i].size();
                for (; j > 0; j--)
                {
                    if (k == 3)
                        break;
                    else if (str[i][j] == ' ')
                        k++;
                    f++;
                }
                str[i].replace(j + 2, f, s);
            }
            else
                str[i].replace(0, str[i].length(), t);
        }
        else
            str[i].replace(0, str[i].length(), t);
    }
    for (int i = 0; i < n; i++)
    {
        cout << str[i] << endl;
    }
    return 0;
}
