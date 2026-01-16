//数据类型：布尔类型bool(1个字节)

//作用：布尔数据类型代表真或假的值
//0代表假，除此之外非0的数字都代表真，其他字符则不会改变其原来的值

#include<iostream>
using namespace std;

int main()
{
    bool flat=true;
    cout<<flat<<"\n";//true代表“真”的意思，（本质上是1）
    flat=false;
    cout<<flat<<"\n";//false代表着“假”的意思，（本质上是0）

    //来测一下占用内存
    cout<<"size of bool="<<sizeof(bool)<<endl;

    system("pause");
    return 0;
}