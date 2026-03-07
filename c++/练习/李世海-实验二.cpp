#include<iostream>
#include<string>
using namespace std;

string word;

void is_huiwen()
{
    int p1 = 0;
    int p2 = word.size() - 1;
    while(p1 < p2)
    {
        if(word[p1] != word[p2])
        {
            cout << "no" << endl;
            return;
        }
        p1++;
        p2--;
    }
    cout << "yes" << endl;
}

int main()
{
    cout << "软件24-1 李世海" << endl;
    cin >> word;
    is_huiwen();
    
    return 0;
}