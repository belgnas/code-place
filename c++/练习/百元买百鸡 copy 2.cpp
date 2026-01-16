#include<iostream>
#include<stdio.h>
using namespace std;
int main()
{
    long long N;
    cin >> N;
    long long arr[N];
    for(long long i = 0; i < N; i++)
    {
        scanf("%lld", &arr[i]);
    }

    long long sum = 0;
    long long num = 0;
    for(long long i = 0; i < N; i++)
    {
        if(2 * arr[i] > arr[N - 1]) break;
        for(long long j = num; j < N; j++)
        {
            if(2 * arr[i] <= arr[j])
            {
                sum += (N - j);
                num = j;
                break;
            }
        }
    }
    cout << sum << endl;
// 6
// 2 3 4 4 7 10


    return 0;
}