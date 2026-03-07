#include<iostream>
using namespace std;

int year, month, day;
int month_day[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void is_l_year()
{
    if(year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
        month_day[1] = 29;
    else
        month_day[1] = 28;
}

int main()
{
    cout << "软件24-1 李世海" << endl;
    cin >> year >> month >> day;
    is_l_year();
    int num_day = 0;
    for(int i = 0; i < month - 1; i++)
    {
        num_day += month_day[i];
    }
    num_day += day;
    
    cout << num_day << endl;
    
    
    return 0;
}