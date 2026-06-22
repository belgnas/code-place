// 复习-基础回顾-学生成绩管理系统
//
// 【诊断目标】
// 通过独立写出本项目，检验以下 C++ 核心知识的掌握程度：
//   1. 封装 — private 成员 + public getter/setter
//   2. 构造/析构 — 带参构造、拷贝构造、初始化列表、析构函数
//   3. 继承 — 基类与派生类、继承方式、构造/析构顺序
//   4. 多态 — 虚函数、纯虚函数、虚析构、动态多态
//   5. 运算符重载 — << 输出、== 比较
//   6. 静态成员 — 统计对象数量
//
// 【项目描述】
// 设计一个学生成绩管理系统，包含：
//   - 抽象基类 Student（学号、姓名、成绩）
//   - 派生类 Undergraduate（本科生 — 增加"论文成绩"）
//   - 派生类 Graduate（研究生 — 增加"项目成绩"）
//   - 成绩管理类 ScoreManager（管理多个学生的增删改查）
//
// 【要求】写代码时不参考旧笔记，暴露薄弱点供后续针对性复习。


#include<iostream>
#include<string>
#include<cstring>
using namespace std;


// ==================== 第一部分：抽象学生基类 ====================

// 抽象学生基类 — 不能直接实例化（纯虚函数）
// 封装学号、姓名、成绩三个核心属性
class Student
{
public:
    // ---- 构造函数 ----

    // 无参构造（默认值）
    Student()
    {
        m_Id = "000000";
        m_Name = "未命名";
        m_Score = 0.0;
        s_Count++;  // 每创建一个学生对象，静态计数 +1
    }

    // 带参构造 + 初始化列表
    // 初始化列表写法: 成员变量(参数值), ...
    // 好处：避免先默认构造再赋值的低效，对 const/引用成员是必须的
    Student(string id, string name, double score) :
        m_Id(id), m_Name(name), m_Score(score)
    {
        s_Count++;
    }

    // 拷贝构造 — 创建一个和已有对象一模一样的新对象
    // 参数必须是 const 引用：避免无限递归 + 不修改原对象
    Student(const Student& other)
    {
        m_Id = other.m_Id;
        m_Name = other.m_Name;
        m_Score = other.m_Score;
        s_Count++;
        cout << "  [拷贝构造] 复制了学生 " << m_Name << endl;
    }

    // ---- 析构函数 ----
    // 虚析构！基类析构必须加 virtual，否则 delete 基类指针时不会调用派生类析构
    virtual ~Student()
    {
        s_Count--;
        // 基类析构通常为空，此处仅作计数维护
    }


    // ---- getter / setter（访问私有成员的唯一通道） ----

    string getId()   const { return m_Id; }
    string getName() const { return m_Name; }
    double getScore()const { return m_Score; }

    void setId(string id)       { m_Id = id; }
    void setName(string name)   { m_Name = name; }
    void setScore(double score) { m_Score = score; }


    // ---- 多态接口 ----

    // 纯虚函数 — 使 Student 成为抽象类，派生类必须重写
    // " = 0 " 表示不提供实现，子类负责实现
    virtual void displayInfo() const = 0;

    // 计算综合成绩 — 普通本科生和研究生的算法不同
    virtual double calcTotalScore() const = 0;


    // ---- 运算符重载 ----

    // 重载 == ：判断两个学生是否同一个人（按学号）
    bool operator==(const Student& other) const
    {
        return m_Id == other.m_Id;
    }

    // 重载 << 输出：友元函数（不是成员函数），这样才能 `cout << stu`
    // 第一个参数是 ostream&（左操作数），第二个是 Student&（右操作数）
    friend ostream& operator<<(ostream& os, const Student& stu)
    {
        os << "学号: " << stu.m_Id
           << "  姓名: " << stu.m_Name
           << "  成绩: " << stu.m_Score;
        return os;  // 返回 ostream& 以实现链式调用 cout << a << b;
    }


    // ---- 静态成员 ----

    // 静态成员函数 — 属于类而非对象，通过 Student::getCount() 调用
    static int getCount() { return s_Count; }

private:
    // 静态成员变量 — 所有对象共享，在类外初始化
    static int s_Count;

protected:
    // protected = 派生类可以访问，外部不能访问
    string m_Id;
    string m_Name;
    double m_Score;       // 考试成绩（100 分制）
};

// 静态成员变量的类外初始化（必须在 .cpp 中，这里写在一起）
int Student::s_Count = 0;


// ==================== 第二部分：派生类 ====================

// 本科生 — 继承 Student
// public 继承：基类 public → 派生类 public，基类 protected → 派生类 protected
class Undergraduate : public Student
{
public:
    // 构造函数 — 先调用基类构造，再初始化自己的成员
    Undergraduate(string id, string name, double examScore, double thesisScore)
        : Student(id, name, examScore)  // 调用基类构造
    {
        m_ThesisScore = thesisScore;
    }

    // 重写纯虚函数 — 本科生显示信息
    virtual void displayInfo() const
    {
        cout << "[本科生] ";
        cout << "学号: " << m_Id
             << "  姓名: " << m_Name
             << "  考试成绩: " << m_Score
             << "  论文成绩: " << m_ThesisScore
             << "  综合成绩: " << calcTotalScore()
             << endl;
    }

    // 本科生综合成绩 = 考试 * 0.7 + 论文 * 0.3
    virtual double calcTotalScore() const
    {
        return m_Score * 0.7 + m_ThesisScore * 0.3;
    }

private:
    double m_ThesisScore;   // 论文成绩
};


// 研究生 — 继承 Student
class Graduate : public Student
{
public:
    Graduate(string id, string name, double examScore, double projectScore)
        : Student(id, name, examScore)
    {
        m_ProjectScore = projectScore;
    }

    virtual void displayInfo() const
    {
        cout << "[研究生] ";
        cout << "学号: " << m_Id
             << "  姓名: " << m_Name
             << "  考试成绩: " << m_Score
             << "  项目成绩: " << m_ProjectScore
             << "  综合成绩: " << calcTotalScore()
             << endl;
    }

    // 研究生综合成绩 = 考试 * 0.5 + 项目 * 0.5
    virtual double calcTotalScore() const
    {
        return m_Score * 0.5 + m_ProjectScore * 0.5;
    }

private:
    double m_ProjectScore;  // 项目成绩
};


// ==================== 第三部分：成绩管理类 ====================

// 管理学生集合 — 封装增删改查逻辑
// 注意：这里用数组模拟，不用 vector（回顾指针和动态内存）
class ScoreManager
{
public:
    // 构造函数
    ScoreManager()
    {
        m_Capacity = 10;                // 初始容量
        m_Size = 0;                     // 当前学生数
        m_Students = new Student*[m_Capacity];  // 动态分配指针数组
        // 初始化为空
        for (int i = 0; i < m_Capacity; i++)
        {
            m_Students[i] = nullptr;
        }
    }

    // 拷贝构造（深拷贝）
    ScoreManager(const ScoreManager& other)
    {
        m_Capacity = other.m_Capacity;
        m_Size = other.m_Size;
        m_Students = new Student*[m_Capacity];

        for (int i = 0; i < m_Size; i++)
        {
            // 注意：这里无法真正深拷贝 Student（它是抽象类）
            // 实际项目中会用 clone() 模式，此处仅做示意
            m_Students[i] = other.m_Students[i];
        }
        cout << "  [警告] ScoreManager 拷贝构造 — 浅拷贝了学生指针！" << endl;
    }

    // 析构函数
    ~ScoreManager()
    {
        // 释放每个学生对象
        for (int i = 0; i < m_Size; i++)
        {
            if (m_Students[i] != nullptr)
            {
                delete m_Students[i];
                m_Students[i] = nullptr;
            }
        }
        // 释放指针数组
        delete[] m_Students;
        m_Students = nullptr;
    }


    // ---- 增删改查 ----

    // 添加学生
    void addStudent(Student* stu)
    {
        // 容量检查，满了就扩容
        if (m_Size >= m_Capacity)
        {
            expand();
        }
        m_Students[m_Size] = stu;
        m_Size++;
        cout << "  [+] 已添加: " << stu->getName() << endl;
    }

    // 按学号删除学生
    bool removeById(string id)
    {
        for (int i = 0; i < m_Size; i++)
        {
            if (m_Students[i]->getId() == id)
            {
                cout << "  [-] 已删除: " << m_Students[i]->getName() << endl;
                delete m_Students[i];

                // 后面的元素向前移动（填补空位）
                for (int j = i; j < m_Size - 1; j++)
                {
                    m_Students[j] = m_Students[j + 1];
                }
                m_Students[m_Size - 1] = nullptr;
                m_Size--;
                return true;
            }
        }
        cout << "  [!] 未找到学号 " << id << " 的学生" << endl;
        return false;
    }

    // 按学号查找
    Student* findById(string id) const
    {
        for (int i = 0; i < m_Size; i++)
        {
            if (m_Students[i]->getId() == id)
            {
                return m_Students[i];
            }
        }
        return nullptr;
    }

    // 显示所有学生（多态 — 每个派生类用自己的 displayInfo）
    void showAll() const
    {
        if (m_Size == 0)
        {
            cout << "  [i] 当前无学生记录" << endl;
            return;
        }
        cout << "\n  ====== 全部学生（共 " << m_Size << " 人）======" << endl;
        for (int i = 0; i < m_Size; i++)
        {
            cout << "  " << (i + 1) << ". ";
            m_Students[i]->displayInfo();  // 多态调用！
        }
        cout << "  ================================" << endl;
    }

    // 获取学生总数
    int getSize() const { return m_Size; }

private:
    // 扩容（容量翻倍）
    void expand()
    {
        int newCapacity = m_Capacity * 2;
        Student** newArr = new Student*[newCapacity];

        // 拷贝旧数据
        for (int i = 0; i < m_Size; i++)
        {
            newArr[i] = m_Students[i];
        }
        // 新位置初始化为空
        for (int i = m_Size; i < newCapacity; i++)
        {
            newArr[i] = nullptr;
        }

        // 释放旧数组（只释放指针数组本身，不释放指向的对象）
        delete[] m_Students;

        m_Students = newArr;
        m_Capacity = newCapacity;
        cout << "  [i] 容量已扩容至 " << m_Capacity << endl;
    }

    Student** m_Students;  // 指向 Student* 数组的指针（二级指针）
    int m_Size;            // 当前学生数
    int m_Capacity;        // 数组容量
};


// ==================== 第四部分：测试函数 ====================

// 测试 1：封装 + 构造 + 静态成员
void test01_encap_construct()
{
    cout << "\n========== 测试1：封装与构造 ==========" << endl;

    // 栈上创建对象
    Undergraduate stu1("2024001", "张三", 85.5, 90.0);
    Graduate     stu2("2024002", "李四", 78.0, 92.0);

    stu1.displayInfo();
    stu2.displayInfo();

    cout << "当前学生对象总数: " << Student::getCount() << endl;

    // 测试 getter/setter
    stu1.setName("张三丰");
    cout << "改名后: " << stu1.getName() << endl;
}

// 测试 2：拷贝构造
void test02_copy_constructor()
{
    cout << "\n========== 测试2：拷贝构造 ==========" << endl;

    Undergraduate stu1("2024003", "王五", 90.0, 85.0);
    stu1.displayInfo();

    // 拷贝构造 — 创建 stu1 的副本
    Undergraduate stu2(stu1);
    stu2.displayInfo();

    // 验证是独立的对象（修改 stu2 不影响 stu1）
    stu2.setName("王五(copy)");
    stu2.setScore(95.0);
    cout << "\n修改副本后:" << endl;
    cout << "原对象: " << stu1.getName() << " 成绩=" << stu1.getScore() << endl;
    cout << "副  本: " << stu2.getName() << " 成绩=" << stu2.getScore() << endl;
}

// 测试 3：继承 + 多态
void test03_polymorphism()
{
    cout << "\n========== 测试3：继承与多态 ==========" << endl;

    // 基类指针指向派生类对象 — 多态的核心用法
    Student* stu1 = new Undergraduate("2024004", "赵六", 88.0, 76.0);
    Student* stu2 = new Graduate("2024005", "田七", 82.0, 91.0);

    // 同一个指针类型，调用不同的 displayInfo
    // 这就是多态 — 运行时根据实际对象类型决定调用哪个函数
    stu1->displayInfo();  // 调用 Undergraduate::displayInfo
    stu2->displayInfo();  // 调用 Graduate::displayInfo

    // 如果用基类指针数组，可以统一管理不同类型的对象
    Student* arr[2] = { stu1, stu2 };
    cout << "\n基类指针数组遍历（多态体现）:" << endl;
    for (int i = 0; i < 2; i++)
    {
        arr[i]->displayInfo();
    }

    // 清理
    delete stu1;
    delete stu2;
}

// 测试 4：运算符重载
void test04_operator_overload()
{
    cout << "\n========== 测试4：运算符重载 ==========" << endl;

    Undergraduate stu1("2024006", "孙八", 75.0, 80.0);
    Undergraduate stu2("2024006", "孙八(copy)", 75.0, 80.0);
    Undergraduate stu3("2024007", "周九", 92.0, 88.0);

    // 测试 << 重载（友元函数）
    cout << stu1 << endl;
    cout << stu2 << endl;

    // 测试 == 重载（按学号比较）
    cout << "stu1 == stu2 ? " << (stu1 == stu2 ? "是" : "否") << endl;
    cout << "stu1 == stu3 ? " << (stu1 == stu3 ? "是" : "否") << endl;
}

// 测试 5：ScoreManager 管理类（综合测试）
void test05_integration()
{
    cout << "\n========== 测试5：综合管理系统 ==========" << endl;

    ScoreManager manager;

    // 添加学生 — 用 new 在堆上创建，manager 负责释放
    manager.addStudent(new Undergraduate("001", "Alice",   85.0, 90.0));
    manager.addStudent(new Graduate("002",     "Bob",     78.0, 88.0));
    manager.addStudent(new Undergraduate("003", "Charlie", 92.0, 85.0));
    manager.addStudent(new Graduate("004",     "Diana",   76.0, 95.0));

    manager.showAll();

    // 查找测试
    cout << "\n查找学号 003:" << endl;
    Student* found = manager.findById("003");
    if (found != nullptr)
    {
        found->displayInfo();
    }

    // 删除测试
    cout << "\n删除学号 002:" << endl;
    manager.removeById("002");
    manager.showAll();
}


// ==================== 主函数 ====================

int main()
{
    cout << "========================================" << endl;
    cout << "|   C++ 复习诊断 — 学生成绩管理系统   |" << endl;
    cout << "========================================" << endl;

    test01_encap_construct();
    test02_copy_constructor();
    test03_polymorphism();
    test04_operator_overload();
    test05_integration();

    cout << "\n[诊断完成] 回顾以上测试中感到吃力的部分，标记为复习重点。" << endl;

    system("pause");
    return 0;
}

// 完结撒花*
