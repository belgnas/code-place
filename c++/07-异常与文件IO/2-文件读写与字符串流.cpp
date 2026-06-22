// 异常处理与文件 IO (2) — 文件读写与字符串流
//
// 【文件流】<fstream>
//   ifstream:  输入文件流（读文件）
//   ofstream:  输出文件流（写文件）
//   fstream:   输入输出文件流（读写）
//
//   ䷛ 继承关系: ios_base → ios → istream/ostream → 文件流/字符串流
//
// 【字符串流】<sstream>
//   istringstream: 输入字符串流（从字符串"读"数据）
//   ostringstream: 输出字符串流（向字符串"写"数据）
//   stringstream:  双向字符串流
//
// 【filesystem】<filesystem> (C++17)
//   跨平台的文件系统操作，替代 POSIX/Windows API


#include<iostream>
#include<fstream>    // ifstream, ofstream, fstream
#include<sstream>    // istringstream, ostringstream, stringstream
#include<filesystem> // path, directory_iterator, ... (C++17)
#include<string>
#include<vector>
#include<iomanip>    // setw, setprecision
using namespace std;
namespace fs = std::filesystem;          // 简化命名空间


// ==================== 第一部分：文件写入 ====================

void test01_file_write()
{
    cout << "\n========== 文件写入 (ofstream) ==========" << endl;

    // ---- 打开文件的几种方式 ----

    // 方式 1：构造时打开
    ofstream fout("test_output.txt");

    // 方式 2：先创建，再打开
    // ofstream fout;
    // fout.open("test_output.txt");

    // ---- 检查是否打开成功 ----
    if (!fout.is_open())
    {
        cerr << "无法打开文件！" << endl;
        return;
    }

    // ---- 写入数据（和 cout 用法完全一样！） ----
    fout << "Hello, 文件IO!" << endl;
    fout << "整数: " << 42 << endl;
    fout << "浮点: " << 3.14159 << endl;
    fout << "布尔: " << boolalpha << true << endl;

    // ---- 格式化写入 ----
    fout << "\n--- 格式化表格 ---" << endl;
    fout << left << setw(10) << "姓名"
         << setw(8)  << "成绩"
         << setw(8)  << "等级" << endl;
    fout << string(26, '-') << endl;
    fout << left << setw(10) << "张三"
         << setw(8)  << 92
         << setw(8)  << "A" << endl;
    fout << left << setw(10) << "李四"
         << setw(8)  << 78
         << setw(8)  << "B" << endl;

    // ---- 关闭文件 ----
    fout.close();
    cout << "文件已写入: test_output.txt" << endl;

    // 打开模式（用 | 组合）:
    // ios::out     写入（默认，覆盖原内容）
    // ios::app     追加（写在文件末尾）
    // ios::binary  二进制模式
    // ios::trunc   打开时清空文件
    // ios::ate     打开时定位到文件末尾

    // 追加模式示例
    ofstream fapp("test_output.txt", ios::app);
    fapp << "\n[追加的内容]" << endl;
    fapp.close();
    cout << "追加写入完成" << endl;
}


// ==================== 第二部分：文件读取 ====================

void test02_file_read()
{
    cout << "\n========== 文件读取 (ifstream) ==========" << endl;

    ifstream fin("test_output.txt");
    if (!fin.is_open())
    {
        cerr << "无法打开文件！" << endl;
        return;
    }

    // ---- 方式 1：逐行读取 ----
    cout << "逐行读取:" << endl;
    string line;
    int lineNum = 0;
    while (getline(fin, line))
    {
        cout << "  L" << (++lineNum) << ": " << line << endl;
    }

    // 重置文件指针到开头
    fin.clear();                         // 清除 EOF 标志
    fin.seekg(0, ios::beg);              // 移动到开头

    // ---- 方式 2：逐词读取 ----
    cout << "\n逐词读取:" << endl;
    string word;
    int wordCount = 0;
    while (fin >> word)
    {
        cout << "  " << word;
        if (++wordCount % 5 == 0) cout << endl;
    }
    if (wordCount % 5 != 0) cout << endl;

    // ---- 方式 3：读取整个文件 ----
    fin.clear();
    fin.seekg(0, ios::beg);
    string content((istreambuf_iterator<char>(fin)),
                    istreambuf_iterator<char>());
    cout << "\n整个文件大小: " << content.length() << " 字节" << endl;

    fin.close();
}


// ==================== 第三部分：二进制文件 ====================

struct StudentRecord
{
    int    id;
    char   name[20];
    double score;
};

void test03_binary_file()
{
    cout << "\n========== 二进制文件读写 ==========" << endl;

    // ---- 写入二进制 ----
    {
        ofstream fout("students.bin", ios::binary);

        StudentRecord students[] =
        {
            {1, "Alice",   92.5},
            {2, "Bob",     85.0},
            {3, "Charlie", 78.5}
        };

        for (const auto& s : students)
        {
            fout.write(reinterpret_cast<const char*>(&s), sizeof(s));
        }

        fout.close();
        cout << "二进制文件写入: students.bin ("
             << (sizeof(students)) << " 字节)" << endl;
    }

    // ---- 读取二进制 ----
    {
        ifstream fin("students.bin", ios::binary);

        cout << "读取二进制文件:" << endl;
        StudentRecord s;
        while (fin.read(reinterpret_cast<char*>(&s), sizeof(s)))
        {
            cout << "  ID: " << s.id
                 << ", 姓名: " << s.name
                 << ", 成绩: " << s.score << endl;
        }

        fin.close();
    }

    // 清理
    remove("students.bin");
}


// ==================== 第四部分：字符串流 ====================

void test04_string_stream()
{
    cout << "\n========== 字符串流 (stringstream) ==========" << endl;

    // ---- ostringstream: 字符串"输出"流（写入到字符串） ----
    // 类似 sprintf，但类型安全 + 自动管理内存

    ostringstream oss;
    oss << "姓名: " << "张三"
        << ", 年龄: " << 20
        << ", 成绩: " << fixed << setprecision(1) << 92.5;

    string result = oss.str();           // 获取构建的字符串
    cout << "ostringstream 结果: " << result << endl;

    // 实用场景：构建 SQL 语句、JSON、日志
    ostringstream sql;
    sql << "SELECT * FROM students WHERE score > " << 80
        << " AND name = '" << "张三" << "'";
    cout << "SQL 示例: " << sql.str() << endl;

    // ---- istringstream: 字符串"输入"流（从字符串解析数据） ----
    // 类似 sscanf，但类型安全 + 可链式读取

    string data = "42 3.14 Hello World";
    istringstream iss(data);

    int    intVal;
    double doubleVal;
    string str1, str2;

    iss >> intVal >> doubleVal >> str1 >> str2;

    cout << "\nistringstream 解析:" << endl;
    cout << "  intVal    = " << intVal << endl;
    cout << "  doubleVal = " << doubleVal << endl;
    cout << "  str1      = " << str1 << endl;
    cout << "  str2      = " << str2 << endl;

    // 实用场景：解析 CSV、配置文件
    string csvLine = "Alice,85,90,92";
    istringstream csvStream(csvLine);
    string name, s1, s2, s3;

    getline(csvStream, name, ',');       // 以 ',' 分隔
    getline(csvStream, s1, ',');
    getline(csvStream, s2, ',');
    getline(csvStream, s3, ',');

    cout << "\nCSV 解析:" << endl;
    cout << "  姓名: " << name
         << ", 成绩: " << s1 << ", " << s2 << ", " << s3 << endl;

    // ---- stringstream: 双向 ----
    stringstream ss;
    ss << 100;                           // 写入
    int val;
    ss >> val;                           // 读回
    cout << "\n双向 stringstream: " << val << endl;
}

void test05_csv_parser()
{
    cout << "\n========== 实战：CSV 解析器 ==========" << endl;

    // 1. 写入 CSV
    {
        ofstream fout("test_data.csv");
        fout << "姓名,年龄,成绩,城市" << endl;
        fout << "张三,20,92.5,北京" << endl;
        fout << "李四,21,85.0,上海" << endl;
        fout << "王五,19,78.5,广州" << endl;
        fout.close();
        cout << "CSV 文件已创建: test_data.csv" << endl;
    }

    // 2. 读取并解析 CSV
    {
        ifstream fin("test_data.csv");
        if (!fin) { cerr << "无法打开文件！" << endl; return; }

        string header;
        getline(fin, header);            // 跳过标题行
        cout << "标题: " << header << endl;

        cout << "\n解析数据:" << endl;
        string line;
        while (getline(fin, line))
        {
            istringstream lineStream(line);
            string name, age, score, city;

            getline(lineStream, name, ',');
            getline(lineStream, age, ',');
            getline(lineStream, score, ',');
            getline(lineStream, city, ',');

            cout << "  " << name
                 << " | " << age << "岁"
                 << " | " << score << "分"
                 << " | " << city << endl;
        }
        fin.close();
    }

    remove("test_data.csv");
    remove("test_output.txt");
}


// ==================== 第五部分：filesystem (C++17) ====================

void test06_filesystem()
{
    cout << "\n========== filesystem (C++17) ==========" << endl;

    // 注意：需要编译器支持 C++17 并链接 stdc++fs
    // g++ -std=c++17 ... -lstdc++fs (GCC 8 及之前)
    // GCC 9+ / MSVC 不需要额外链接

    fs::path currentPath = fs::current_path();
    cout << "当前工作目录: " << currentPath << endl;

    // 路径操作
    fs::path filePath = currentPath / "test_dir" / "example.txt";
    cout << "\n路径拼接: " << filePath << endl;
    cout << "  父目录:   " << filePath.parent_path() << endl;
    cout << "  文件名:   " << filePath.filename() << endl;
    cout << "  扩展名:   " << filePath.extension() << endl;
    cout << "  不带扩展: " << filePath.stem() << endl;

    // 创建目录
    fs::path testDir = currentPath / "test_fs_demo";
    if (!fs::exists(testDir))
    {
        fs::create_directory(testDir);
        cout << "\n创建目录: " << testDir << endl;
    }

    // 创建一些文件
    for (int i = 1; i <= 3; i++)
    {
        ofstream fout(testDir / ("file_" + to_string(i) + ".txt"));
        fout << "这是文件 " << i << endl;
        fout.close();
    }

    // 遍历目录
    cout << "\n遍历目录 " << testDir.filename() << ":" << endl;
    for (const auto& entry : fs::directory_iterator(testDir))
    {
        cout << "  ";
        if (entry.is_directory())
            cout << "[目录] ";
        else if (entry.is_regular_file())
            cout << "[文件] ";
        cout << entry.path().filename()
             << " (" << entry.file_size() << " 字节)" << endl;
    }

    // 检查文件属性
    cout << "\n文件属性:" << endl;
    fs::path aFile = testDir / "file_1.txt";
    if (fs::exists(aFile))
    {
        cout << "  文件存在: " << fs::exists(aFile) << endl;
        cout << "  文件大小: " << fs::file_size(aFile) << " 字节" << endl;
        // 获取最后修改时间等需要 <chrono> 转换
    }

    // 清理测试目录
    fs::remove_all(testDir);
    cout << "\n测试目录已清理" << endl;
}


int main()
{
    cout << "========================================" << endl;
    cout << "| 异常处理与文件IO(2) — 文件与字符串流|" << endl;
    cout << "========================================" << endl;

    test01_file_write();
    test02_file_read();
    test03_binary_file();
    test04_string_stream();
    test05_csv_parser();
    test06_filesystem();

    system("pause");
    return 0;
}

// 完结撒花*
