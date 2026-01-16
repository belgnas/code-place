// P1115 最大子段和

// 题目描述
// 给出一个长度为n的序列a，选出其中连续且非空的一段使得这段和最大。

// 输入格式
// 第一行是一个整数，表示序列的长度n。
// 第二行有n个整数，第i个整数表示序列的第i个数字aⅰ。
// 输出格式
// 输出一行一个整数表示答案。

#include<iostream>
using namespace std;
int main()
{
	//优化前

	// int n = 0;
	// cin >> n;
	// int a[200010], b[200010];
	// int answer;
	// for(int i = 1; i <= n; i++)
	// {
	// 	cin >> a[i];
	// 	if(i == 1) b[i] = a[i], answer = a[i];
	// 	else 
	// 	{
	// 		b[i] = max(a[i], b[i - 1] + a[i]);
	// 	}
	// 	answer = max(answer, b[i]);

	// }
	
	// cout << answer << endl;
	

	//优化后

	int n = 0;
	cin >> n;
	int a, b;
	int answer;
	for(int i = 1; i <= n; i++)
	{
		cin >> a;
		if(i == 1) b = a, answer = a;
		else 
		{
			b = max(a, b + a);
			answer = max(answer, b);
		}
		

	}

	cout << answer << endl;

	return 0;
}