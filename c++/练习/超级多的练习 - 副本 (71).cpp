#include <bits/stdc++.h>

using namespace std;

#define IOS ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

int main()
{
    IOS;

    int N;
    cin >> N;
    vector<string> words;
    string word;
    
    while (N--)
    {
        cin >> word;
        words.push_back(word);
    }

    int k;
    cin >> k;
    cin.ignore(); // 忽略上一次输入后残留的换行符，避免影响后续 getline 的读取

    string passage;
    getline(cin, passage);

    int cnt = 0;
    string replacement = "######"; // 用于临时替换敏感词的字符串

    for (const string &w : words)
    {
        size_t pos = passage.find(w);
        while (pos != string::npos)
        {                                                      
            cnt++;                                             
            passage.replace(pos, w.length(), replacement);     
            pos = passage.find(w, pos + replacement.length());
        }
    }

    if (cnt >= k)
    {
        cout << cnt << '\n' << "He Xie Ni Quan Jia!" << "\n";
    }
    else
    {
        size_t pos = passage.find(replacement);
        while (pos != string::npos)
        {
            passage.replace(pos, replacement.length(), "<censored>");
            pos = passage.find(replacement, pos + string("<censored>").length());
        }
        cout << passage << "\n";
    }

    return 0;
}