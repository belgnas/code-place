// 妹纸是什么? 我只是看重两人相互舔舐伤口的温暖

// 类和对象-多态-案例2-制作饮品

// 案例描述：
// 制作饮品的大致流程为：煮水 - 冲泡 - 倒入杯中 - 加入辅料

// 利用多态技术实现本案例，提供抽象制作饮品基类，提供子类制作咖啡和茶叶

#include<iostream>
using namespace std;

class AbstractDrinking
{
public:

    // 煮水
    virtual void Boil() = 0;

    // 冲泡
    virtual void Brew() = 0;

    // 倒入杯中
    virtual void  PourInCup() = 0;

    // 加入辅料
    virtual void PutSomething() = 0;

    // 制作饮品
    void makeDrink()
    {
        Boil();
        Brew();
        PourInCup();
        PutSomething();
    }
};

// 制作咖啡
class Coffee : public AbstractDrinking
{
public:
    // 煮水
    virtual void Boil()
    {
        cout << "煮农夫山泉" << endl;
    }

    // 冲泡
    virtual void Brew()
    {
        cout << "冲泡咖啡" << endl;
    }

    // 倒入杯中
    virtual void  PourInCup()
    {
        cout << "倒入咖啡杯中" << endl;
    }

    // 加入辅料
    virtual void PutSomething()
    {
        cout << "加入糖和牛奶" << endl;
    }
};

// 制作茶水
class Tea : public AbstractDrinking
{
public:
    // 煮水
    virtual void Boil()
    {
        cout << "煮矿泉水" << endl;
    }

    // 冲泡
    virtual void Brew()
    {
        cout << "冲泡茶叶" << endl;
    }

    // 倒入杯中
    virtual void  PourInCup()
    {
        cout << "倒入茶杯中" << endl;
    }

    // 加入辅料
    virtual void PutSomething()
    {
        cout << "加入枸杞" << endl;
    }
};

// 制作函数
void doWork(AbstractDrinking * abs) // AbstractDrinking * abs = new Coffee
{
    abs->makeDrink();

    delete abs; // 手动释放
}

void test01()
{
    // 制作咖啡
    doWork(new Coffee);

    cout << "---------------" << endl;

    // 制作茶水
    doWork(new Tea);
}


int main()
{
    test01();

    return 0;
}