//数据类型：实型/浮点型变量

//作用：表示小数
//单精度：float（4字节）
//双精度：double（8字节）
//默认情况下，输出一个小数会显示出6位有效数字（ps：这里的有效数字是指有效的数字，如3.14有3位有效数字

#include<iostream>
using namespace std;

int main()
{
    float f1=3.141f;//这里的f是强调该数字要用float处理,否则会默认用doublt处理
    cout<<"f1="<<f1<<"\n";

    double d1=1.414;//这里不能加d，是因为默认就是double
    cout<<"d1="<<d1<<"\n";


    //比较少用的方法：科学计数法
    float f2=3e4;//3*10^4
    cout<<"f2="<<f2<<"\n";

    float f3=3e-4;//3*0.1^4
    cout<<"f3="<<f3<<"\n";

    system("pause");
    return 0;
}