//goto语句（ps：就是传送锚点）

//作用：可以无条件地跳转语句

//ps:警告：不要频繁使用，会严重影响阅读（尽量不要使用）

//语法：goto 标记;
//解释：如果标记的名称存在，执行到goto语句时，会跳转到标记的位置

#include<iostream>
using namespace std;

int main()
{
    cout<<"1.****"<<endl;
    cout<<"2.****"<<endl;
    cout<<"3.****"<<endl; 

    goto FLAG;

    cout<<"4.****"<<endl;
    cout<<"5.****"<<endl;

    FLAG://ps：这里是冒号！

    cout<<"6.****"<<endl; 
    
    system("pause");

    return 0;   
}