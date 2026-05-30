#include <iostream>
#include <vector>
using namespace std;

vector<int> constructArray(int n)
{
    vector<int> arr;
    if (n == 1)
    {
        arr.push_back(1);
        return arr;
    }
    arr = {1, 2};
    for (int len = 2; len < n; ++len)
    {
        int newElement;
        for (int candidate = 1; candidate <= n; ++candidate)
        {
            bool valid = true;
            for (int start = 0; start <= len; ++start)
            {
                vector<int> count(n + 1, 0);
                for (int i = start; i <= len; ++i)
                {
                    if (i < len)
                    {
                        count[arr[i]]++;
                    }
                    else
                    {
                        count[candidate]++;
                    }
                }
                bool hasUnique = false;
                for (int j = 1; j <= n; ++j)
                {
                    if (count[j] == 1)
                    {
                        hasUnique = true;
                        break;
                    }
                }
                if (!hasUnique)
                {
                    valid = false;
                    break;
                }
            }
            if (valid)
            {
                newElement = candidate;
                break;
            }
        }
        arr.push_back(newElement);
    }
    return arr;
}

int main()
{
    int n;
    cin >> n;
    vector<int> arr = constructArray(n);
    vector<bool> exists(n + 1, false);
    int kindCount = 0;
    for (int num : arr)
    {
        if (!exists[num])
        {
            kindCount++;
            exists[num] = true;
        }
    }
    cout << kindCount << endl;
    for (int i = 0; i < arr.size(); ++i)
    {
        if (i > 0)
        {
            cout << " ";
        }
        cout << arr[i];
    }
    cout << endl;
    return 0;
}