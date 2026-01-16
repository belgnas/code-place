// #include<iostream>
// using namespace std;
// int main()
// {
//     int a = 0;
//     int *p;
//     p = &a;

//     *p = 999999;
//     cout << a;



//     return 0;
// }

#include <iostream>

using namespace std;

int main() 
{
    int a = 0;
    char *p;

    p = reinterpret_cast<char *>(&a);

    int valueToSet = 999999;
    char *valuePtr = reinterpret_cast<char *>(&valueToSet);

    for (int i = 0; i < static_cast<int>(sizeof(int)); i++) {
        p[i] = valuePtr[i];
    }

    cout << a;

    return 0;
}