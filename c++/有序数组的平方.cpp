#include<iostream>
#include<vector>
using namespace std;

int main()
{
    vector<int> arr = {-4, -1, 0, 3, 10};

    int k = arr.size() - 1;
    
    vector<int> answer(arr.size(), 0);

    for(int i = 0, j = arr.size() - 1; i <= j;/*这里省略，写在for循环里面*/)
    {
        if(arr[i] * arr[i] < arr[j] * arr[j])
        {
            answer[k] = arr[j] * arr[j];
            k--;
            j--;
        }
        else
        {
            answer[k] = arr[i] * arr[i];
            k--;
            i++;
        }
    }

    for(int i : answer)
    {
        cout << i << " ";
    }
    cout << endl;
    
    
    return 0;
}