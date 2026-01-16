#include<iostream>
#include<vector>
using namespace std;

void inverse(vector<int> * x, int n, int * p_f, int * p_s)
{
    for(int i = 0; i < n; i++)
    {
        if((*x)[i] > *p_f)
        {
            *p_s = *p_f;
            *p_f = (*x)[i];
        }
        else if((*x)[i] > *p_s)
        {
            *p_s = (*x)[i];
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<int>arr (n, 0);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    int len = arr.size();
    int p_f = 0, p_s = 0;
    inverse(&arr, len, &p_f, &p_s);
    
    printf("%d %d", p_f, p_s);
    
    return 0;
}