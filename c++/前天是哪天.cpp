#include <iostream>
#include <string>

using namespace std;

int main()
{
    string ar;
    cin >> ar;

    int year, month, day;
    year = (ar[0] - '0') * 1000 + (ar[1] - '0') * 100 + (ar[2] - '0') * 10 + (ar[3] - '0');
    month = (ar[5] - '0') * 10 + (ar[6] - '0');
    day = (ar[8] - '0') * 10 + (ar[9] - '0');

    if (day > 2)
    {
        day -= 2;
    }
    else
    {
        if (month == 3 && day == 1)
        {
            if (((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
            {
                // 闰年，29
                month = 2;
                day = 28;
            }
            else
            {
                // 平年，28
                month = 2;
                day = 27;
            }
        }
        else if (month == 1 && day == 1)
        {
            year--;
            month = 12;
            day = 30;
        }
        else
        {
            switch (month)
            {
            case 2:
                if (day == 1)
                {
                    if (((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
                    {
                        // 闰年，29
                        month = 1;
                        day = 28;
                    }
                    else
                    {
                        // 平年，28
                        month = 1;
                        day = 27;
                    }
                }
                else
                {
                    month--;
                    day = 31;
                }
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                if (day == 30)
                {
                    month--;
                    day = 29;
                }
                else if (day == 1)
                {
                    month--;
                    day = 30;
                }
                else
                {
                    month--;
                    day = 31;
                }
                break;
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if (day == 1)
                {
                    month--;
                    day = 30;
                }
                else
                {
                    month--;
                    day = 31;
                }
                break;
            }
        }
    }

    cout << year << "-";
    if (month < 10)
        cout << "0" << month << "-";
    else
        cout << month << "-";

    if (day < 10)
        cout << "0" << day;
    else
        cout << day;

    cout << endl;

    return 0;
}