// 栈 （先进后出）

// // ************************** 栈

// int stk[N], tt;

// // 插入
// stk[++tt] = x;
// // 弹出
// tt--;

// // 判断栈是否为空
// if (tt > 0) // 不空
// else empty;

// // 栈顶
// stk[tt];

// // **************************

#include <iostream>
using namespace std;

const int N = 100010;

int stk[N];
int tt = 0;

// 插入到栈顶
void push(int x)
{
    stk[++tt] = x;
}

// 弹出栈顶元素
void pop()
{
    tt--;
}

// 判断栈区是否为空
bool is_Empty() // 这里不要命名为 is_empty 因为会和编译器内置的函数名字冲突
{
    return tt == 0;
}

void remove_whole()
{
    tt = 0;
}

// print 栈顶
void print_Top()
{
    if(tt > 0)
    {
        cout << stk[tt - 1] << endl;
    } 
    else
    {
        cout << "栈为空，无栈顶元素可输出" << endl;
    }
}

void print_stk()
{
    cout << "( 栈顶 -> 栈底 )：";
    for(int i = tt - 1; i > 0; i--)
    {
        cout << stk[i] << " ";
    }
    cout << endl;
}

int main()
{

    push(1);
    push(2);
    push(3);
    cout << "弹出前的栈：";
    print_stk(); // 栈顶 -> 栈底

    cout << "弹出前的栈顶元素：";
    print_Top(); // 栈顶 -> 栈底

    if(is_Empty()) cout << "此时栈为空" << endl;
    else cout << "此时栈不为空" << endl;

    pop();
    cout << "弹出后的栈：";
    print_stk(); // 栈顶 -> 栈底

    remove_whole();
    cout << "清空后的栈：";
    print_stk(); // 栈顶 -> 栈底


    return 0;
}