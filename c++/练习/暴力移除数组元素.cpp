#include<iostream>
#include<vector>
using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<int> stones(N);
    for (int i = 0; i < N; i++)
    {
        cin >> stones[i];
    }
    for (int year = 0; year < N; year++)
    {
        int n = year;
        for (int j = 0; j < n; j++)
        {
            if (stones[j] > 0)
            {
                stones[j]--;
                stones[n]++;
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        cout << stones[i] << " ";
    }
    cout << endl;

    return 0;
}