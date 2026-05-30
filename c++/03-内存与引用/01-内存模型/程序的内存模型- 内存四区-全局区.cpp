//2.全局区：存放全局变量和静态变量以及常量

//  * 全局变量 和 静态常量 存放在此
//  *全局区还包括了常量区， 字符串常量 和 其他常量（比如const） 也存放在此
//  ！！该区域的数据在结束后由操作系统释放！！（不是由人决定的）


/*
    本文用到的缩写：
        c- const  固定的
        g- global  全局的
        l- local  局部的
*/


/*
    总结： 
    * C++中在程序运行前分为全局区和代码区
    * 代码区的特点是共享和只读
    * 全局区中存放着全局变量、静态常量、const修饰的局部变量（也叫做 局部常量/常量 ）
    * 常量区中存放着 const修饰的全局常量（也叫做 全局变量 ）和字符串常量

*/  

#include<iostream>
using namespace std;

//全局变量
int g_a = 10;
int g_b = 10;

//const修饰的全局变量，也叫做全局常量
const int c_g_a = 10;
const int c_g_b = 10;

int main()
{
    //全局区
    //全局变量、静态变量、常量
    

    //创建普通局部变量
    int a = 10;
    int b = 10;

    cout << "局部变量a的地址为：" << (long long)&a << endl;
    //这里用long long是因为数据量溢出，int不够大
    cout << "局部变量b的地址为：" << (long long)&b << endl;

    cout << "全局变量g_a的地址为：" << (long long)&g_a << endl;
    cout << "全局变量g_b的地址为：" << (long long)&g_b << endl;


    //静态变量   在普通变量的前面加static，属于静态变量
    static int s_a = 10;
    static int s_b = 10;
    cout << "静态变量s_a的地址为：" << (long long)&s_a << endl;
    cout << "静态变量s_b的地址为：" << (long long)&s_b << endl;

    
    //常量
    //字符串常量
    cout << "字符串常量的地址为：" << (long long)&"hello world" << endl;


    //const修饰的变量
    // 1. const修饰的全局变量 也叫做 全局常量 
    cout << "全局常量c_g_a的地址为：" << (long long)&c_g_a << endl;
    cout << "全局常量c_g_b的地址为：" << (long long)&c_g_b << endl;

    // 2. const修饰的局部变量 也叫做 局部常量 
    int c_l_a = 10;
    int c_l_b = 10;

    cout << "局部常量c_l_a的地址为：" << (long long)&c_l_a << endl;
    cout << "局部常量c_l_b的地址为：" << (long long)&c_l_b << endl;


    return 0;
}