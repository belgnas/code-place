#include<iostream>
#include<string>
#include<cmath>
#include<vector>
using namespace std;

vector<int>z_num;

bool isPrime(int num)//不是ai
{
    for(int i : z_num)
    {
        if(num == i) return true;
        else
        {
            if (num <= 3) return num - 1;
        // 不在6的倍数两侧的一定不是质数
            if (num % 6!= 1 && num % 6!= 5) return false;
    
            for (int i = 5; i <= int(sqrt(num)); i += 6) 
            {
                if (num % i == 0 || num % (i + 2) == 0)
                {
                    z_num.push_back(i);
                    return false;
                }
            }
    
    
            return true;
        }
    }
    return true;
}

void answer(bool is)
{
    bool answer = isPrime(is);
    if(answer)
    {
        cout << "prime" << endl;
    }
    else
    {
        cout << "noprime" << endl;
    }
}




int main()
{
    int T;
    cin >> T;
    int num;
    while(T--)
    {
        cin >> num;
        bool is = isPrime(num);
        if(is)
        {
            cout << "isprime" << endl;
            cout << num << endl;
        }
        else
        {
            cout << "noprime" << endl;
            for(int i = 2; i <= num; i++)
            {
                if(num % i == 0)
                {
                    bool is_2 = isPrime(i);
                    if(is_2)
                    {
                        cout << i << " ";
                    }
                }
            }
            cout << endl;
        }
    }

    
    
    return 0;
}