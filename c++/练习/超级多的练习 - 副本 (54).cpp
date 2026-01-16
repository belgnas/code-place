#include<iostream>
#include<string>
using namespace std;



int main()
{
    string password;
    string answer;
    getline(cin, password);
    for(char ar : password)
    {
        if(ar == '[')
        {
            break;
        }
        cout << ar;
    }
    for(long long i = 0; i < static_cast<long long>(password.length()); i++)
    {
        if(password[i] == '[')
        {
            long long num = 1;
            string word = "";
            int n = 0;
            while(password[i] != ']')
            {
                i++;
                if(password[i] - '0' <= 9 && password[i] - '0' >= 0)
                {
                    num *= (password[i] - '0');
                }
                else
                {
                    if(password[i] != '[' && password[i] != ']')
                    {
                        word += password[i];
                    }
                    
                }
            }
            
            for(long long j = 0; j < num; j++)
            {
                cout << word;
            }
            
        }
    }



    return 0;
}