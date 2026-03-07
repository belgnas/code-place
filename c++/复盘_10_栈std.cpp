#include <iostream>
#include <stack>
#include <string>
using namespace std;

// 功能：打印栈的核心信息（仅展示关键状态，简洁版）
void printStack(const stack<int>& st, const string& title) {
    cout << "【" << title << "】" << endl;
    cout << "  - 是否为空：" << (st.empty() ? "是" : "否") << endl;
    cout << "  - 元素个数：" << st.size() << endl;
    if (!st.empty()) {
        cout << "  - 栈顶元素：" << st.top() << endl;
    }
    cout << "----------------------------------------" << endl;
}

// 功能：括号匹配（栈的经典应用，仅支持()）
bool isBracketValid(const string& s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(') {
            st.push(c);
        } else if (c == ')') {
            if (st.empty()) return false; // 右括号多余
            st.pop();
        }
    }
    return st.empty(); // 左括号无剩余则匹配
}

int main() {
    // ======================================
    // 模块1：栈的基础初始化
    // ======================================
    stack<int> st; // 核心：空栈初始化（最常用）
    printStack(st, "初始化空栈");

    // ======================================
    // 模块2：栈的核心操作（push/top/pop）
    // ======================================
    // 1. 入栈（push）
    st.push(10);
    st.push(20);
    st.push(30);
    printStack(st, "入栈 10/20/30 后");

    // 2. 访问栈顶（top）
    int topVal = st.top();
    cout << "单独获取栈顶：" << topVal << endl;
    cout << "----------------------------------------" << endl;

    // 3. 出栈（pop）：仅删除，无返回值
    st.pop(); // 删除30
    printStack(st, "弹出栈顶（30）后");
    st.pop(); // 删除20
    printStack(st, "再次弹出栈顶（20）后");

    // ======================================
    // 模块3：栈的遍历（核心：弹出式遍历，会清空）
    // ======================================
    // 重新填充数据
    st.push(5);
    st.push(15);
    st.push(25);
    cout << "【遍历栈（弹出所有元素）】" << endl;
    cout << "  弹出顺序：";
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << "\n----------------------------------------" << endl;
    printStack(st, "遍历后（栈清空）");

    // ======================================
    // 模块4：经典应用 - 括号匹配
    // ======================================
    cout << "【括号匹配测试】" << endl;
    string cases[] = {"()()", "(()", ")(", "((()))"};
    for (const string& s : cases) {
        cout << "  \"" << s << "\"：" << (isBracketValid(s) ? "匹配" : "不匹配") << endl;
    }

    return 0;
}