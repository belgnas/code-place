// ==================== 学生信息管理系统 ====================
//
// 【项目概述】
//   多文件 C++17 项目，整合了 C++ 复习计划中的核心知识点：
//   ✓ STL 容器 (vector, map)          — 数据存储
//   ✓ 智能指针 (unique_ptr)           — 内存管理（零 new/delete）
//   ✓ 模板 (Repository<T>)            — 泛型数据仓库
//   ✓ 多态 (Person → Student/Teacher) — 统一管理不同类型
//   ✓ Lambda + STL 算法               — 查找、排序、筛选
//   ✓ 异常处理                        — 文件读写、输入验证
//   ✓ 文件 I/O (CSV 持久化)           — 数据保存和加载
//   ✓ RAII (fstream)                  — 异常安全的资源管理
//   ✓ CMake 构建                      — 跨平台编译
//
// 【项目结构】
//   include/  Person.h, Student.h, Teacher.h, Repository.h, FileManager.h, Utils.h
//   src/      Person.cpp, Student.cpp, Teacher.cpp, FileManager.cpp, Utils.cpp
//   main.cpp  主程序入口


#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<algorithm>
#include<iomanip>

#include"Person.h"
#include"Student.h"
#include"Teacher.h"
#include"Repository.h"
#include"FileManager.h"
#include"Utils.h"

using namespace std;


// ==================== 全局数据 ====================

// 用 Repository<Person> 管理所有人（学生 + 教师）
// 多态：基类指针管理派生类对象
Repository<Person> g_Repository;

// 数据文件名
const string DATA_FILE = "students_data.csv";


// ==================== 菜单与功能 ====================

void showMenu()
{
    cout << "\n";
    cout << "========================================" << endl;
    cout << "|     学生信息管理系统 v1.0          |" << endl;
    cout << "|======================================|" << endl;
    cout << "|  [1] 添加学生                       |" << endl;
    cout << "|  [2] 添加教师                       |" << endl;
    cout << "|  [3] 显示全部人员                   |" << endl;
    cout << "|  [4] 按学号/工号查找                |" << endl;
    cout << "|  [5] 按姓名模糊搜索                 |" << endl;
    cout << "|  [6] 删除人员                       |" << endl;
    cout << "|  [7] 按角色筛选（学生/教师）        |" << endl;
    cout << "|  [8] 统计信息                       |" << endl;
    cout << "|  [9] 保存到文件                     |" << endl;
    cout << "| [10] 从文件加载                     |" << endl;
    cout << "|  [0] 退出系统                       |" << endl;
    cout << "========================================" << endl;
    cout << "请选择操作: ";
}

// 添加学生
void addStudent()
{
    cout << "\n--- 添加学生 ---" << endl;

    string id, name, major;
    int age;
    double score;

    cout << "学号: ";
    cin >> id;
    cin.ignore();

    // 检查重复
    if (g_Repository.findById(id) != nullptr)
    {
        cout << "[!] 学号 " << id << " 已存在！" << endl;
        return;
    }

    cout << "姓名: ";
    getline(cin, name);

    age   = Utils::readInt("年龄", 1, 150);
    cout << "专业: ";
    getline(cin, major);
    score = Utils::readDouble("成绩", 0.0, 100.0);

    // make_unique — 零 new，自动内存管理
    g_Repository.add(make_unique<Student>(id, name, age, major, score));
    cout << "[✓] 学生 " << name << " 添加成功！" << endl;
}

// 添加教师
void addTeacher()
{
    cout << "\n--- 添加教师 ---" << endl;

    string id, name, title, course;
    int age;

    cout << "工号: ";
    cin >> id;
    cin.ignore();

    if (g_Repository.findById(id) != nullptr)
    {
        cout << "[!] 工号 " << id << " 已存在！" << endl;
        return;
    }

    cout << "姓名: ";
    getline(cin, name);

    age    = Utils::readInt("年龄", 1, 150);
    cout << "职称 (讲师/副教授/教授): ";
    getline(cin, title);
    cout << "授课科目: ";
    getline(cin, course);

    g_Repository.add(make_unique<Teacher>(id, name, age, title, course));
    cout << "[✓] 教师 " << name << " 添加成功！" << endl;
}

// 显示全部人员（多态遍历）
void showAll()
{
    auto all = g_Repository.getAll();

    if (all.empty())
    {
        cout << "\n[i] 暂无数据，请先添加或加载。" << endl;
        return;
    }

    cout << "\n===== 全部人员 (" << all.size() << " 人) =====" << endl;

    // Lambda + for_each 遍历
    for_each(all.begin(), all.end(),
        [](const Person* p) { p->display(); });
}

// 按 ID 查找
void findById()
{
    string id;
    cout << "\n请输入学号/工号: ";
    cin >> id;

    auto* person = g_Repository.findById(id);
    if (person)
    {
        person->display();
    }
    else
    {
        cout << "[!] 未找到 ID 为 " << id << " 的人员。" << endl;
    }
}

// 按姓名模糊搜索
void findByName()
{
    string keyword;
    cout << "\n请输入姓名关键词: ";
    cin.ignore();
    getline(cin, keyword);

    auto results = g_Repository.findByName(keyword);

    if (results.empty())
    {
        cout << "[!] 未找到包含 \"" << keyword << "\" 的人员。" << endl;
        return;
    }

    cout << "\n===== 搜索结果 (" << results.size() << " 条) =====" << endl;
    for (const auto* p : results)
    {
        p->display();
    }
}

// 删除人员
void removePerson()
{
    string id;
    cout << "\n请输入要删除的学号/工号: ";
    cin >> id;

    if (g_Repository.removeById(id))
    {
        cout << "[✓] ID " << id << " 已删除。" << endl;
    }
    else
    {
        cout << "[!] 未找到 ID 为 " << id << " 的人员。" << endl;
    }
}

// 按角色筛选
void filterByRole()
{
    cout << "\n选择角色: [1] 学生  [2] 教师: ";
    int choice;
    cin >> choice;

    string role = (choice == 1) ? "学生" : "教师";
    auto results = g_Repository.getByRole(role);

    if (results.empty())
    {
        cout << "[i] 暂无" << role << "记录。" << endl;
        return;
    }

    cout << "\n===== " << role << "列表 (" << results.size() << " 人) =====" << endl;
    for (const auto* p : results)
    {
        p->display();
    }
}

// 统计信息
void showStatistics()
{
    auto all = g_Repository.getAll();

    if (all.empty())
    {
        cout << "\n[i] 暂无数据，无法统计。" << endl;
        return;
    }

    auto students = g_Repository.getByRole("学生");
    auto teachers = g_Repository.getByRole("教师");

    cout << "\n===== 统计信息 =====" << endl;
    cout << "总人数:   " << all.size() << " 人" << endl;
    cout << "  学生:   " << students.size() << " 人" << endl;
    cout << "  教师:   " << teachers.size() << " 人" << endl;

    // 学生成绩分析
    if (!students.empty())
    {
        // 用 Lambda 从学生指针提取成绩
        vector<double> scores;
        scores.reserve(students.size());
        for (const auto* p : students)
        {
            if (auto* s = dynamic_cast<const Student*>(p))
            {
                scores.push_back(s->getScore());
            }
        }

        // STL 算法：最大、最小、平均
        auto [minIt, maxIt] = minmax_element(scores.begin(), scores.end());
        double sum = accumulate(scores.begin(), scores.end(), 0.0);
        double avg = sum / scores.size();

        cout << "\n学生成绩分析:" << endl;
        cout << "  最高分: " << fixed << setprecision(1) << *maxIt << endl;
        cout << "  最低分: " << *minIt << endl;
        cout << "  平均分: " << avg << endl;

        // 统计各等级人数
        int gradeCount[5] = {0};  // A B C D F
        for (double s : scores)
        {
            if      (s >= 90) gradeCount[0]++;
            else if (s >= 80) gradeCount[1]++;
            else if (s >= 70) gradeCount[2]++;
            else if (s >= 60) gradeCount[3]++;
            else             gradeCount[4]++;
        }
        cout << "  等级分布: A=" << gradeCount[0]
             << " B=" << gradeCount[1]
             << " C=" << gradeCount[2]
             << " D=" << gradeCount[3]
             << " F=" << gradeCount[4] << endl;
    }

    // 教师统计
    if (!teachers.empty())
    {
        cout << "\n教师统计:" << endl;
        for (const auto* p : teachers)
        {
            if (auto* t = dynamic_cast<const Teacher*>(p))
            {
                cout << "  " << t->getName()
                     << " | " << t->getTitle()
                     << " | " << t->getCourse() << endl;
            }
        }
    }
}

// 保存到文件
void saveData()
{
    auto all = g_Repository.getAll();

    if (all.empty())
    {
        cout << "\n[i] 暂无数据，不需要保存。" << endl;
        return;
    }

    if (FileManager::saveToCSV(DATA_FILE, all))
    {
        cout << "[✓] 数据已保存。" << endl;
    }
}

// 从文件加载
void loadData()
{
    cout << "\n正在从 " << DATA_FILE << " 加载数据..." << endl;

    auto persons = FileManager::loadFromCSV(DATA_FILE);

    if (persons.empty()) return;

    // 将加载的数据移动到 Repository
    for (auto& p : persons)
    {
        g_Repository.add(move(p));
    }
    // persons 中的空 unique_ptr 离开作用域自动析构（安全的）
    cout << "[✓] 加载完成。" << endl;
}


// ==================== 主函数 ====================

int main()
{
    cout << "========================================" << endl;
    cout << "|  学生信息管理系统 — C++ 综合项目    |" << endl;
    cout << "|  STL + 智能指针 + 模板 + 多态 + I/O |" << endl;
    cout << "========================================" << endl;

    // 启动时自动加载已有数据
    loadData();

    // 主循环
    while (true)
    {
        showMenu();

        int choice;
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[!] 请输入有效数字！" << endl;
            continue;
        }

        try
        {
            switch (choice)
            {
            case 1:  addStudent();      break;
            case 2:  addTeacher();      break;
            case 3:  showAll();         break;
            case 4:  findById();        break;
            case 5:  findByName();      break;
            case 6:  removePerson();    break;
            case 7:  filterByRole();    break;
            case 8:  showStatistics();  break;
            case 9:  saveData();        break;
            case 10: loadData();        break;
            case 0:
                cout << "\n退出前自动保存..." << endl;
                saveData();
                cout << "再见！(￣▽￣)ノ" << endl;
                return 0;
            default:
                cout << "[!] 无效选项，请重新选择。" << endl;
            }
        }
        catch (const exception& e)
        {
            cerr << "[异常] " << e.what() << endl;
            cerr << "  程序继续运行，数据未受影响。" << endl;
        }

        if (choice != 3 && choice != 8)  // 这些操作完不需要暂停
        {
            Utils::pause();
        }
        else
        {
            system("pause");
        }
    }

    return 0;
}

// 完结撒花*
//
// 【项目总结】
// 本项目综合运用了以下 C++ 核心技能：
//   1. STL: vector, map, sort, find_if, for_each, accumulate, minmax_element
//   2. 智能指针: unique_ptr + make_unique（零 new/delete）
//   3. 模板: Repository<T> 泛型数据仓库
//   4. 多态: Person 基类 → Student/Teacher 派生类
//   5. Lambda: 自定义排序、查找条件、遍历操作
//   6. 异常处理: try/catch 保护文件操作，输入验证
//   7. 文件 I/O: CSV 格式持久化，fstream RAII
//   8. 设计模式: Repository 模式、工厂方法 (parseLine)
//   9. CMake: 跨平台构建配置
//
// 完成本项目和所有学习文件后，可以：
//   → 进入「Linux 系统编程」学习阶段
//   → 或开始「C++ 高并发 WebServer」项目
