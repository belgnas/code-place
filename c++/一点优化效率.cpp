    // 关闭iostream与stdio的同步，提高输入输出效率
        //ios::sync_with_stdio(false);

    // 解除cin与cout的绑定，进一步提高输入输出效率
        //cin.tie(0);

    // 解除cout与cin的绑定，进一步提高输入输出效率
        //cout.tie(0);

#include<iostream>
using namespace std;

int main()
{
    // 关闭iostream与stdio的同步，提高输入输出效率
    ios::sync_with_stdio(false);

    // 解除cin与cout的绑定，进一步提高输入输出效率
    cin.tie(0);

    // 解除cout与cin的绑定，进一步提高输入输出效率
    cout.tie(0);
    
    system("pause");

    return 0;   
}   