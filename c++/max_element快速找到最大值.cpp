#include<iostream>
#include<algorithm>
#include<iomanip>
using namespace std;

int main()
{
    int T;
    cin >> T;
    for(int i = 0; i < T; i++)
    {
        int n;
        cin >> n;
        int arr[n];
        double average = 0;
        for(int j = 0; j < n; j++)
        {
            cin >> arr[j];
            average += arr[j];
        }
        //cout << *max_element(arr, arr + n) << "~~~~~~~" << *min_element(arr, arr + n);
        cout << *max_element(arr, arr + n) - *min_element(arr, arr + n);
        cout << " ";
        average /= n;
        double sum = 0;
        for(int j = 0; j < n; j++)
        {
            sum += (arr[j] - average) * (arr[j] - average);
        }
        sum /= n;
        cout << fixed << setprecision(3) << sum;
        cout << endl;
    }
    
    return 0;
}