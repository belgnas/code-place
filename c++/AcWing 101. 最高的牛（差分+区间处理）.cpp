// 最高的牛

// 题目
//  链接https://www.acwing.com/problem/content/description/103/

// 题目描述
//  有 N 头牛站成一行，被编队为 1、2、3…N，每头牛的身高都为整数。
//  当且仅当两头牛中间的牛身高都比它们矮时，两头牛方可看到对方。
//  现在，我们只知道其中最高的牛是第 P 头，它的身高是 H ，剩余牛的身高未知。
//  但是，我们还知道这群牛之中存在着 M 对关系，每对关系都指明了某两头牛 A 和 B 可以相互看见。
//  求每头牛的身高的最大可能值是多少。

// 输入格式
//  第一行输入整数 N,P,H,M，数据用空格隔开。
//  接下来 M 行，每行输出两个整数 A 和 B ，代表牛 A 和牛 B 可以相互看见，数据用空格隔开。

// 输出格式
//  一共输出 N 行数据，每行输出一个整数。第 i 行输出的整数代表第 i 头牛可能的最大身高。

// 数据范围
//  1≤N≤5000,
//  1≤H≤1000000,
//  1≤A,B≤10000,
//  0≤M≤10000

// 样例输入
// 样例：
//  9 3 5 5
//  1 3
//  5 3
//  4 3
//  3 7
//  9 8

// 输出样例：
//  5
//  4
//  5
//  3
//  4
//  4
//  5
//  5
//  5
//  注意??：此题中给出的关系对可能存在重复!!!
#include <iostream>
#include <algorithm>
using namespace std;

const int num = 5010;

int N,P,H,M;// N:牛的数量，P:最高位置，H:最高高度，M:M对关系
int n[num], m[10010][2];// n：差分数列；

bool compare_2(const int* a, const int* b)
{
    return a[0] == b[0] && a[1] == b[1];
}

int main()
{
    // 输入数据
    cin >> N >> P >> H >> M;
    for(int i = 1; i <= M; i++)
    {
        cin >> m[i][0] >> m[i][1];
        if(m[i][0] > m[i][1]) swap(m[i][0], m[i][1]);
    }

    // // sort(m + 1, m + 1 + M, compare_2);
    // for(int i = 1; i <= M; i++) cout << m[i][0] << " " << m[i][1] << endl;
    
    // 计算差分数组
    n[1] = H;
    for(int i = 1; i <= M; i++)
    {
        n[m[i][0] + 1]--;
        n[m[i][1]]++;
    }

    // for(int i = 1; i <= N; i++) cout << n[i] << " ";

    for(int i = 1; i <= N; i++)
    {
        n[i] += n[i - 1];
        cout << n[i] << endl;
    }
    

    return 0;
}