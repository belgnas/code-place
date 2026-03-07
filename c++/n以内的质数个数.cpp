#include<iostream>
#include<cmath>
using namespace std;

bool isPrime(int num);

int test(int num)
{
    int answer = 0;
    for(int i = 0; i <= num; i++)
    {
        if(isPrime(i)) answer++;
    }
    return answer;
    
}

bool isPrime(int num)
{
    if (num <= 3) return num > 1;
    // 不在6的倍数两侧的一定不是质数
    if (num % 6!= 1 && num % 6!= 5) return false;

    for (int i = 5; i <= int(sqrt(num)); i += 6) 
    {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }

    return true;
}

int main()
{
    int t,n;
    
    cin >> t;
    while(t--)
    {
        cin >> n;
        cout << test(n) << endl;
    }
    return 0;
}