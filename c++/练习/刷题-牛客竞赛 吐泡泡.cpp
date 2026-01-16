#include<iostream>
#include<string>
using namespace std;
#define IOS ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

char arr[100010];
int op;

void init()
{
    op = 0;
}

bool empty()
{
    if(op == 0) return true;
    else return false;
}

bool size_1()
{
    if(op == 1) return true;
    else return false;
}

void insert(char x)
{
    op ++;
    arr[op] = x;
    while(!empty() && !size_1() && arr[op] == arr[op - 1])
    {
        if(arr[op] == 'O' && arr[op - 1] == 'O')
        {
            op -= 2;
        }
        else if(arr[op] == 'o' && arr[op - 1] == 'o')
        {
            op --;
            arr[op] = 'O';
        }
    }
}

void print()
{
    for(int i = 1; i <= op; i++)
    {
        cout << arr[i];
    }
    cout << endl;
}

int main()
{
    IOS;
    
    string str;
    while(cin >> str)
    {
        init();
        
        for(int i = 0; i < static_cast<int>(str.length()); i++)
        {
            insert(str[i]);
        }

        print();
    }
    
    
    
    return 0;
}