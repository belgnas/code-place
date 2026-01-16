//先说一句：Ciallo～(∠?ω< )⌒★
//Ciallo～(∠?ω< )⌒★Ciallo～
//0721

//能不能通过计算出字符串的长度，然后从右往左，
//提取每一个字符的ASCII编码，随后用这个编码减去64得到位置，
//最后通过26进制的原理来计算出位置？

/*#include<iostream>
#include<string>
#include<cmath>
using namespace std;

int main()
{
    string S;
    cin >> S;
    int length = S.length();
    int arr[length];//引入一个数组存放各个字符的相对位置
    int j = 0;
    for(int i = length - 1; i>=0; i--)//从右往左
    {
        arr[j] = (int)S[i] - 64;  // 获取字符的ASCII编码，减去64得到相对位置（A为1，以此类推）
        j++;
    }   
    int numble;
    int answer = arr[0];
    for (int k = 1; k<length; k++)
    {
        numble = pow(26,k);
        answer += numble;
    }
    cout << answer;
    
    
    system("pause");

    return 0;   
}*/




//先说一句：Ciallo～(∠?ω< )⌒★
//Ciallo～(∠?ω< )⌒★Ciallo～
//0721

//能不能通过计算出字符串的长度，然后从右往左，
//提取每一个字符的ASCII编码，随后用这个编码减去64得到位置，
//最后通过26进制的原理来计算出位置？

#include<iostream>
#include<string>
#include<cmath>
using namespace std;

int main()
{
    string S;
    cin >> S;
    int length = S.length();
    int arr[length];//引入一个数组存放各个字符的相对位置
    int j = 0;
    for(int i = length - 1; i>=0; i--)//从右往左
    {
        arr[j] = (int)S[i] - 64;  // 获取字符的ASCII编码，减去64得到相对位置（A为1，以此类推）
        j++;
    }   
    long long numble;
    long long answer = arr[0];
    for (int k = 1; k<length; k++)
    {
        numble = arr[k]*pow(26,k);
        answer += numble;
    }
    cout << answer;
    
    
    system("pause");

    return 0;   
}