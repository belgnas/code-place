#include<iostream>
#include<vector>
using namespace std;
int main()
{
    vector<int> arr = {1, 2, 1, 1, 1, 4, 1, 5, 1, 6};
    
    int num = 1;
    
    int s_p = 0;//???
    for(int f_p = 0;/*???*/ f_p < static_cast<int>(arr.size()); f_p++)
    {
        if(arr[f_p] != num)
        {
            arr[s_p] = arr[f_p];
            s_p++;
        }
    }

    cout << s_p << endl;

    return 0;
}