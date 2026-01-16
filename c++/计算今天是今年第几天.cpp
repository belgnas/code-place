#include<iostream>
using namespace std;
int main()
{
    int year,month,day;
    int rili[12][31] = {0};
    cin >> year >> month >> day;
    for(int i = 0; i < 12; i++)
    {
        if(i + 1 == 1 || i + 1 == 3 || i + 1 == 5 || i + 1 == 7 || i + 1 == 8 || i + 1 == 10 || i + 1 == 12)
        {
            for(int j = 0; j < 31; j++)
            {
                rili[i][j] = 1;
            }
        }
        else if(i + 1 == 4 || i + 1 == 6 || i + 1 == 9 || i + 1 == 11)
        {
            for(int j = 0; j < 30; j++)
            {
                rili[i][j] = 1;
            }
        }
        else if(i + 1 == 2)
        {
            if(((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
            {
                for(int j = 0; j < 29; j++)
                {
                    rili[i][j] = 1;
                }
            }
            else
            {
                for(int j = 0; j < 28; j++)
                {
                    rili[i][j] = 1;
                }
            }
        }
    }
    
    int sum = 0;
    for(int i = 0; i < month; i++)
    {
        if(i + 1 < month)
        {
            for(int j = 0; j < 31; j++)
            {
                sum += rili[i][j];
            }
            //cout << sum << endl;
            //sum = 0;
        }
        else if(i + 1 == month)
        {
            for(int j = 0; j < day; j++)
            {
                sum += rili[i][day];
            }       
        }

    }
    
    cout << sum << endl;
    
    
    
    return 0;
}