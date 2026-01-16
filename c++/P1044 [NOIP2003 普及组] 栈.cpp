// P1044 [NOIP2003 ÆÕ¼°×é] Õ»

#include<iostream>
using namespace std;

int arr[20][20] = {0};

int test(int jin, int zhan)
{
    if(arr[jin][zhan]) return arr[jin][zhan]; 
	if(jin == 0) return 1; 
	if(zhan > 0) arr[jin][zhan] += test(jin, zhan - 1);
	arr[jin][zhan] += test(jin - 1, zhan + 1);
    return arr[jin][zhan];
}

int main()
{
    int n;
    cin >> n;
    int zhan = 0;
    int jin = n;
    cout << test(jin, zhan) << endl;


    return 0;
}


// #include<iostream>

// using namespace std;

// long long test(long long jin, long long chu, long long n)
// {
    
//     sum++;
//     cout << sum << " ";

//     if(jin == 0)
//     {
//         return 1;
//     }
//     if(jin == n) return test(jin - 1, chu, n);
//     if(jin == 0) return test(jin, chu - 1, n);
//     if(jin > chu) return 0;
//     return test(jin - 1, chu, n) + test(jin, chu - 1, n);

// }

// int main()
// {
//     long long n;
//     cin >> n;
//     long long jin = n;
//     long long chu = n;
//     long long sum = test(jin, chu, n);
//     cout << sum << endl;


//     return 0;
// }

