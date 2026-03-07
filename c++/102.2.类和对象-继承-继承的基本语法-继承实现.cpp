// 晚上多学0.5个小时，早上早起多学0.5个小时


// 类和对象-继承-继承的基本语法

// 继承的好处：减少重复代码 （这点在写项目的时候非常重要） 
// 语法：class 子类 : 继承方式 父类（拓展：继承方式一共有3种，我们这一节使用的继承方式是公共继承，这3种的继承方式下一节会系统地学习）

// ps：一些专业术语
// 子类 也称为 派生类
// 父类 也称为 基类

// 派生类中的成员，包含 两大部分
//  一类是从基类继承过来的，一类是自己增加的成员
// 从基类继承过来的表现其共性，而新增的成员体现了其个性

// 继承是面向对象三大特性之一
// 有些类和类之间存在特殊关系，例如大类会包括小类，小类又会包括更小的类

// 我们发现，定义这些类时，下级别的成员除了拥有上一级的共性，还会有自己的特性
// 这个时候我们就可以考虑用 继承 的技术，减少重复代码

// 继承的基本语法

// 例如我们看到的很多网站中，都有公共的头部，公共的底部，甚至公共的左侧列表，只有中心内容不同
// 接下来我们分别用普通写法和继承的写法来实现网页中的内容，看一下继承存在的意义和好处

#include<iostream>
using namespace std;

// 继承实现

// 公共页面
class BasePage
{
public:
    void header()
    {
        cout << "首页、公开课、登录、注册...（公共头部）" << endl;
    }
    void footer()
    {
        cout << "帮助中心、交流合作、站内地图...（公共底部）" << endl;
    }
    void left()
    {
        cout << "Java、Python、C++...（公共分类列表）" << endl;
    }

};

// Java页面
class Java : public BasePage
{
public:
    void content()
    {
        cout << "Java学科视频" << endl;
    }
};

// Python页面
class Python : public BasePage
{
public:
    void content()
    {
        cout << "Python学科视频" << endl;
    }
};

// C++页面
class CPP : public BasePage
{
public:
    void content()
    {
        cout << "C++学科视频" << endl;
    }
};

void test01()
{
    cout << "Java的视频页面如下：" << endl;
    Java ja;
    ja.header();
    ja.footer();
    ja.left();
    ja.content();

    cout << "--------------分割线--------------" << endl;

    cout << "Python的视频页面如下：" << endl;
    Python py;
    py.header();
    py.footer();
    py.left();
    py.content();

    cout << "--------------分割线--------------" << endl;

    cout << "C++的视频页面如下：" << endl;
    CPP cpp;
    cpp.header();
    cpp.footer();
    cpp.left();
    cpp.content();
}

int main()
{
    test01();


    return 0;
}