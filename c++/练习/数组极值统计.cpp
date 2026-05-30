#include<iostream>
#include<vector>
using namespace std;

void inverse(vector<double> * x, int n, double * p_max, double * p_min, double * p_mid)
{
    for(int i = 0; i < n; i++)
    {
        if((*x)[i] > *p_max)
        {
            *p_max = (*x)[i];
        }
        if((*x)[i] < *p_min)
        {
            *p_min = (*x)[i];
        }
        *p_mid += (*x)[i];
    }
    *p_mid /= n;
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<double>arr (n, 0);
    for(int i = 0; i < n; i++)
    {
        scanf("%lf", &arr[i]);
    }
    int len = arr.size();
    double p_max = 0, p_min = 100, p_mid = 0;
    inverse(&arr, len, &p_max, &p_min, &p_mid);
    
    printf("%.2lf %.2lf %.2lf", p_max, p_min, p_mid);
    
    return 0;
}