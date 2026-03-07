// 双指针算法 加油

//作用：可以将O(n?)的复杂度简化到O(n)

#include <iostream>
#include <string.h>
using namespace std;
int main()
{
    char str[1000];

    gets(str);

    int n = strlen(str);

    for(int i = 0; i < n; i++)
    {
        int j = i;
        while(j < n && str[j] != ' ') j++;
        for(int k = i; k <= j; k++) cout << str[k];
        cout << endl;

        i = j;
    } 
    

    return 0;
}