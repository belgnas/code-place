#include<iostream>
#include<string>
#include<cmath>

using namespace std;

bool isPrime(int num)//不是ai
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
    int num;
    cin >> num;

    int reversed_num = 0;
    int temp = num;

    // 通过数学运算逆序生成回文数
    while (temp > 0) {
        reversed_num = reversed_num * 10 + temp % 10;
        temp /= 10;
    }

    bool answer = isPrime(reversed_num);
    if(answer)
    {
        cout << "prime" << endl;
    }
    else
    {
        cout << "noprime" << endl;
    }
    
    
    return 0;
}