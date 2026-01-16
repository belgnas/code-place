//通讯录管理系统

/*
实现功能：
菜单功能：
添加联系人：向通讯录中添加联系人，信息包括（姓名、性别、年龄、联系电话、家庭住址），最多纪录1000人。
    实现步骤：
    1.设计联系人结构体
    2.设计通讯录结构体
    3.main函数中创建通讯录
    4.封装添加联系人函数
    5.测试添加联系人功能

显示联系人：显示通讯录中所有联系人信息
    实现步骤：
    1.封装显示联系人函数
        思路：判断如果当前通讯录没有人，就提示记录为空，人数大于0，显示通讯录中的信息
    2.测试显示联系人功能

删除联系人：按照名字进行删除指定联系人
    实现步骤：
    1.封装检测联系人是否存在
    2.封装删除联系人函数
    3.测试删除联系人功能

查找联系人：按照姓名查看指定联系人信息
    实现步骤：
    1.封装查找联系人函数
    2.测试查找联系人函数
    实现思路：判断指定用户是否存在，如果存在显示信息，不存在则提示查无此人

修改联系人：按照姓名重新修改指定联系人
    实现步骤：
    1.封装修改联系人函数
    2.测试修改联系人函数
    实现思路：查找用户输入的联系人，如果查找成功进行修改操作，查找失败提示查无此人

清空联系人：清空通讯录中所有信息
    实现步骤：
    1.封装清空联系人函数
    2.测试清空联系人
    实现思路：将通讯录中所有的联系人信息清除掉，只需要将通讯录记录的联系人的数量置为0，做逻辑清空即可

退出通讯录：退出当前使用的通讯录
*/

#include<iostream>
#include<cstring>
using namespace std;
#define MAX 1000//宏常量

//设计联系人结构体
struct Person
{
    //姓名
    string m_Name;
    //性别 1 男  2 女
    int m_Sex;
    //年龄
    int m_Age;
    //电话
    string m_Phone;
    //住址
    string m_Addr;
};

//设计通讯录结构体
struct Addressbooks
{
    //通讯录中保存的联系人的数组
    struct Person PersonArray[MAX];
    //通讯录中当前记录的联系人的个数
    int m_Size;
};

//1.添加联系人
void addPerson(Addressbooks * abs)
{
    //判断通讯录是否已满，如果满了就不再添加
    if(abs->m_Size == MAX)
    {
        cout << "满了呀，加不了了呀" << endl;
        return;
    }
    else
    {
        //添加具体联系人

        //姓名
        string name;
        cout << "汝可以输入名字：" << endl;
        cin >> name;
        abs->PersonArray[abs->m_Size].m_Name = name;

        //性别
        cout << "是男生？还是女生？" << endl;
        cout << "1----男生" << endl;
        cout << "2----女生" << endl;
        int sex = 0;

        while(true)
        {
            //只能输入1或2，否者就是输入有误，无限循环直到输入了1或2
            cin >> sex;
            if(sex == 1 || sex == 2)
            {
                abs->PersonArray[abs->m_Size].m_Sex = sex;
                break;
            }
            cout << "汝只能输入“男生”和“女生”的说！" << endl;
        }

        //年龄
        cout << "请汝说出这个人的年纪：" << endl;
        int age = 0;
        cin >> age;
        abs->PersonArray[abs->m_Size].m_Age = age;

        //电话
        cout << "汝说出的这个人联系电话：" << endl;
        string phone;
        cin >> phone;
        abs->PersonArray[abs->m_Size].m_Phone = phone;

        //地址
        cout << "汝还要说出这个人的的家在哪里：" << endl;
        string addr;
        cin >> addr;
        abs->PersonArray[abs->m_Size].m_Addr = addr;

        //更新通讯录人数
        abs->m_Size++;

        cout << "已经记住汝所说的话了......" << endl;

        system("pause");//请按任意键继续

        system("cls");//清屏操作

    }
}

//2.显示所有的联系人
void showPerson(Addressbooks * abs)
{
    //判断如果当前通讯录没有人，就提示记录为空
    //如果人数大于0，显示通讯录中的信息
    if(abs->m_Size == 0)
    {
        cout << "汝不告诉我，我什么都不知道" << endl;
        system("pause");
        system("cls");//清屏
    }
    else
    {
        for(int i = 0; i < abs->m_Size; i++)
        {
            cout << "名字是：" << abs->PersonArray[i].m_Name << endl;
            cout << "性别是" << (abs->PersonArray->m_Sex == 1 ? "男生" : "女生") << endl;
            cout << "年纪是" << abs->PersonArray->m_Age << endl;
            cout << "电话是" << abs->PersonArray->m_Phone << endl;
            cout << "家是在" << abs->PersonArray->m_Addr << endl;

            cout << endl;
        }
        system("pause");//请按任意键继续

        system("cls");//清屏操作
    }
}

//检测联系人是否存在（如果存在，返回联系人所在数组中的具体位置，不存在返回-1）
int isExist(Addressbooks * abs, string name)
{
    for(int i = 0; i< abs->m_Size; i++)
    {
        //找到用户输入的姓名了
        if(abs->PersonArray[i].m_Name == name)
        {
            return i;//找到了，返回这个人在数组中的下标编号
        }
    }
    return -1;//如果遍历结束都没有找到，返回-1
}

//3.删除指定联系人
void deletePerson(Addressbooks * abs)
{
    cout << "请汝说出要删除谁" << endl;

    string name;
    cin >> name;

    //ret == -1  未查到
    //ret != -1  查到了
    int ret = isExist(abs, name);

    if(ret != -1)
    {
        //查找到人，要进行删除操作
        for(int i = ret; i < abs->m_Size; i++)
        {
            //数据前移
            abs->PersonArray[i] = abs->PersonArray[i + 1];
        }
        abs->m_Size--;//更新通讯录中前移的操作
        cout << "保证完成汝的删除任务的说" << endl;
    }
    else
    {
        cout << "汝明明没有允许咱认识这个人" << endl;
    }

    system("pause");
    system("cls");//清屏
}

//4.查找指定的联系人信息
void findPerson(Addressbooks * abs)
{
    cout << "请汝说出汝想要找的人" << endl;
    string name;
    cin >> name;

    //判断指定的联系人是否存在通讯录中
    int ret = isExist(abs, name);
    
    if(ret != -1)//找到联系人
    {
        cout << "汝找的是" << abs->PersonArray[ret].m_Name << endl;
        cout << "性别是" << (abs->PersonArray->m_Sex == 1 ? "男生" : "女生") << endl;
        cout << "年纪是" << abs->PersonArray[ret].m_Age << endl;
        cout << "电话是" << abs->PersonArray[ret].m_Phone << endl;
        cout << "家是在" << abs->PersonArray[ret].m_Addr << endl;
    }
    else//未找到联系人
    {
        cout << "汝明明没有允许咱认识这个人" << endl;
    }

    //按下任意键后清屏
    system("pause");
    system("cls");
}

//5.修改指定联系人的信息
void modifyPersonal(Addressbooks * abs)
{
    cout << "请汝说出汝想要更新谁的信息" << endl;
    string name;
    cin >> name;

    int ret = isExist(abs, name);

    if(ret != -1)//找到指定联系人
    {
        cout << "杂鱼主人，汝想要修改，就让汝全部说一遍好啦"  << endl;
        
        //姓名
        string name;
        cout << "名字是" << endl;
        cin >> name;
        abs->PersonArray[ret].m_Name = name;

        //性别
        cout << "是男生？还是女生？" << endl;
        cout << "1----男生" << endl;
        cout << "2----女生" << endl;
        int sex = 0;

        while(true)
        {
            cin >> sex;
            if(sex == 1 || sex == 2)
            {
                //输入正确，退出循环
                abs->PersonArray[ret].m_Sex = sex;
                break;
            }
            cout << "汝只能输入“男生”和“女生”的说!" << endl;
        }

        //年龄
        cout << "年纪是" << endl;
        int age = 0;
        cin >> age;
        abs->PersonArray[ret].m_Age = age;

        //电话
        cout << "电话是" << endl;
        string phone;
        cin >> phone;
        abs->PersonArray[ret].m_Phone = phone;

        //住址
        cout << "家是在" << endl;
        string address;
        cin >> address;
        abs->PersonArray[ret].m_Addr = address;
        
        cout << "已经记住汝所说的话啦.....最喜欢的杂鱼主人！" << endl;
    }
    else//未找到联系人
    {
        cout << "汝明明没有允许咱认识这个人" << endl;
    }
    
    //按任意键清屏
    system("pause");
    system("cls");
}

//清空所有联系人
void cleanPerson(Addressbooks * abs)
{
    abs->m_Size = 0;//将当前记录联系人的数量置为0，做逻辑清空操作
    cout << "记忆已被清空，主人" << endl;
    
    //按任意键清屏
    system("pause");
    system("cls");
}

//菜单界面
void showMenu()
{
    cout << "**************************" << endl;
    cout << "*****  1.添加联系人  *****" << endl;
    cout << "*****  2.显示联系人  *****" << endl;
    cout << "*****  3.删除联系人  *****" << endl;
    cout << "*****  4.查找联系人  *****" << endl;
    cout << "*****  5.修改联系人  *****" << endl;
    cout << "*****  6.清空联系人  *****" << endl;
    cout << "*****  0.退出通讯录  *****" << endl;
    cout << "**************************" << endl;
}

int main()
{
    cout << "杂鱼主人你来啦，等你好久啦" << endl << endl;
    //创建通讯录结构体变量
    Addressbooks abs;
    //初始化通讯录中当前人员个数
    abs.m_Size = 0;

    int select = 0;//创建用户选择输入的变量

    while(true)
    {
        //菜单调用
        showMenu();

        cin >> select;

        switch(select)
        {
            case 1://1.添加联系人
                addPerson(&abs);//利用地址传递，可以修饰实参
                break;

            case 2://2.显示联系人
                showPerson(&abs);
                break;

            case 3://3.删除联系人

            /*测试用代码

            {//这里的花括号的使用是因为switch里的代码太长，需要括起来
                cout << "请汝说出要删除谁？" << endl;
                string name;
                cin >> name;

                if(isExist(&abs, name) == -1)
                {
                    cout << "汝明明没有允许咱认识这个人" << endl;
                }
                else
                {
                    cout << "保证完成汝的删除任务的说" << endl;
                }
            }
            */
           
                deletePerson(&abs);
                break;

            case 4://4.查找联系人
                findPerson(&abs);
                break;

            case 5://5.修改联系人
                modifyPersonal(&abs);
                break;

            case 6://6.清空联系人
                cleanPerson(&abs);
                break;

            case 0://0.退出通讯录
                cout << "汝下次继续使用,好吗？" << endl;
                return 0;
                break;
        }
    }
    

    return 0;
}

//完结撒花★