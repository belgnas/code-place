// 类和对象-多态-案例3-电脑组装

// 案例描述：
// 电脑主要组成部件为CPU（用于计算），显卡（用于显示），内存条（用于存储）
// 将每个零件封装出抽象基类，并且提供不同的厂商生产不同的零件，例如Intel厂商和Lenovo厂商
// 创建电脑类提供让电脑工作的函数，并且调用每个零件工作用的接口
// 测试时组装三台不同的电脑进行工作


// // 伪代码
// 抽象出每个零件的类
// class CPU 抽象类
// {
//     // 抽象计算函数
//     virtual void calculate() = 0;
// };
// class VideoCard 抽象类
// {
//     // 抽象显示函数
//     virtual void display() = 0;
// };
// class Memory 抽象类
// {
//     // 抽象存储函数
//     virtual void display() = 0; 
// };
//
// 电脑类
// class Computer
// {
//     构造函数传入三个零件指针
//
//     提供工作的函数
//     {
//         调用每个零件工作的接口
//     }
// };
//
// 具体零件的厂商
// Inter 厂商
// class IntelCPU  : public _cputws
// {
//     void calculate()
//     {
//         cout << "Intel的CPU开始计算了！" << endl;
//     }
// };
// Lenovo厂商
// 也需要三个零件


#include<iostream>
using namespace std;

// 抽象不同零件类
// 抽象CPU类
class CPU
{
public:
    // 抽象的计算函数
    virtual void calculate() = 0;
};
// 抽象显卡类
class VideoCard
{
public:
    // 抽象的显示函数
    virtual void display() = 0;
};
// 抽象内存条类
class Memory
{
public:
    // 抽象的存储函数
    virtual void storage() = 0;
};

// 电脑类
class Computer
{
public:
    Computer(CPU * cpu, VideoCard * vc, Memory * mem)
    {
        m_cpu = cpu;
        m_vc = vc;
        m_mem = mem;
    }

    // 提供工作的函数
    void work()
    {
        // 让零件工作起来,调用接口
        m_cpu->calculate();
        m_vc->display();
        m_mem->storage();
    }

    // 提供析构函数 释放3个电脑零件
    ~ Computer()
    {
        // 释放CPU零件
        if(m_cpu != NULL)
        {
            delete m_cpu;
            m_cpu = NULL;
        }

        // 释放显卡零件
        if(m_vc != NULL)
        {
            delete m_vc;
            m_vc = NULL;
        }

        // 释放内存条零件
        if(m_mem != NULL)
        {
            delete m_mem;
            m_mem = NULL;
        }
    }

private:

    CPU * m_cpu; // CPU的零件指针
    VideoCard * m_vc; // 显卡零件指针
    Memory * m_mem; // 内存条零件指针
};

// 具体厂商
// Intel厂商-CPU
class IntelCPU : public CPU
{
public:
    virtual void calculate()
    {
        cout << "Intel的CPU开始计算了！" << endl;
    }
};
// Intel厂商-显卡
class IntelVideoCard : public VideoCard
{
public:
    virtual void display()
    {
        cout << "Intel的显卡开始显示了！" << endl;
    }
};
// Intel厂商-内存条
class IntelMemory : public Memory
{
public:
    virtual void storage()
    {
        cout << "Intel的内存条开始存储了！" << endl;
    }
};

// Lenovo厂商-CPU
class LenovoCPU : public CPU
{
public:
    virtual void calculate()
    {
        cout << "Lenovo的CPU开始计算了！" << endl;
    }
};
// Lenovo厂商-显卡
class LenovoVideoCard : public VideoCard
{
public:
    virtual void display()
    {
        cout << "Lenovo的显卡开始显示了！" << endl;
    }
};
// Lenovo厂商-内存条
class LenovoMemory : public Memory
{
public:
    virtual void storage()
    {
        cout << "Lenovo的内存条开始存储了！" << endl;
    }
};

void test01()
{
    // 第一台电脑组装

    // 第一台电脑零件
    CPU * intelCpu  = new IntelCPU;
    VideoCard * intelCard = new IntelVideoCard;
    Memory * intelMem = new IntelMemory;
    // 创建第一台电脑
    Computer * computer1 = new Computer(intelCpu, intelCard, intelMem);
    computer1->work();
    delete computer1;

    cout << "-----------------" << endl;

    // 第二台电脑组装
    cout << "第2台电脑开始工作" << endl;

    Computer * computer2 = new Computer(new LenovoCPU, new LenovoVideoCard, new LenovoMemory);
    computer2->work();
    delete computer2;

    cout << "-----------------" << endl;

    // 第三台电脑组装
    cout << "第3台电脑开始工作" << endl;

    Computer * computer3 = new Computer(new IntelCPU, new IntelVideoCard, new LenovoMemory);
    computer3->work();
    delete computer2;

}

int main()
{
    test01();

    return 0;
}