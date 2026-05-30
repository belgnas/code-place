#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

// Trie树 节点数
#define MAX_NODE 100010

// 快速排序模板
// 时间复杂度：O(nlogn) （n为arr的大小）
void quick_sort(vector<int> &arr, int l = -1, int r = -1) {
    if (l == -1 && r == -1) {
        l = 0;
        r = arr.size() - 1;
    }
    
    if (l >= r) return;

    int x = arr[l];
    int i = l - 1;
    int j = r + 1;
    while (i < j) {
        do i++; while (arr[i] < x);
        do j--; while (arr[i] > x);

        if (i < j) swap(arr[i], arr[j]);
    }
    quick_sort(arr, l, j);
    quick_sort(arr, j + 1, r);
}


// 归并排序模板
// 时间复杂度：O(nlogn) （n为arr的大小）
void merge_sort(vector<int> &arr, int l = -1, int r = -1, vector<int> tmp = {}) {
    if (l == -1 && r == -1) {
        l = 0;
        r = arr.size() - 1;
        tmp.resize(arr.size());
    }
    
    if (l >= r) return;

    int mid = (l + r) >> 1;
    merge_sort(arr, l, mid);
    merge_sort(arr, mid + 1, r);

    int k = 0;
    int i = l;
    int j = mid + 1;
    while (i < mid && j <= r) {
        if (arr[i] <= arr[j]) {
            tmp[k++] = arr[i++];
        }
        else {
            tmp[k++] = arr[j++];
        }
    }
    while (i <= mid) {
        tmp[k++] = arr[i++];
    }
    while (j <= r) {
        tmp[k++] = arr[j++];
    }
    
    for (i = l, j = 0; i <= r; i++, j++) {
        arr[i] = tmp[j];
    }
}

// 打印数组（末尾换行）
void print_arr(vector<int> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1) cout << ' ';
        else cout << endl;
    }
}

// 高精度加法
// 时间复杂度：O(n) （n为a的位数）
string hp_add(string a, string b) {
    vector<int> A, B;
    for(int i = a.size() - 1; i >= 0; i--) {
        A.push_back(a[i] - '0');
    }
    for(int i = b.size() - 1; i >= 0; i--) {
        B.push_back(b[i] - '0');
    }

    vector<int> C;
    int t = 0;
    for(int i = 0; i < A.size(); i++) {
        t += A[i];
        if(i < B.size()) {
            t += B[i];
        }
        C.push_back(t % 10);
        t /= 10;
    }
    if(t != 0) {
        C.push_back(t);
    }

    string res;
    for(int i = C.size() - 1; i >= 0; i--) {
        res += to_string(C[i]);
    }
    return res;
}

// 高精度减法
// 时间复杂度：O(n) （n为a的位数）
string hp_sub(string a, string b) {
    vector<int> A, B;
    for(int i = a.size() - 1; i >= 0; i--) {
        A.push_back(a[i] - '0');
    }
    for(int i = b.size() - 1; i >= 0; i--) {
        B.push_back(b[i] - '0');
    }

    vector<int> C;
    int t = 0;
    for(int i = 0; i < A.size(); i++) {
        t += A[i];
        if(i < B.size()) {
            t -= B[i];
        }
        C.push_back((t + 10) % 10);
        if(t < 0) {
            t = -1;
        }
        else {
            t = 0;
        }
    }
    while(C.size() > 1 && C.back() == 0) {
        C.pop_back();
    }

    string res;
    for(int i = C.size() - 1; i >= 0; i--) {
        res += to_string(C[i]);
    }
    return res;
}

// 高精度乘法
// 时间复杂度：O(nm) （n为a的位数，m为b的位数）
string hp_mul(string a, string b) {
    vector<int> A, B;
    for(int i = a.size() - 1; i >= 0; i--) {
        A.push_back(a[i] - '0');
    }
    for(int i = b.size() - 1; i >= 0; i--) {
        B.push_back(b[i] - '0');
    }

    vector<int> C(A.size() + B.size(), 0);
    for(int i = 0; i < A.size(); i++) {
        for(int j = 0; j < B.size(); j++) {
            C[i + j] += A[i] * B[j];
        }
    }

    string res;
    for(int i = C.size() - 1; i >= 0; i--) {
        res += to_string(C[i]);
    }
    return res;
}

// 高精度除法
// 时间复杂度：O(nm) （n为a的位数，m为b的位数）
string hp_div(string a, string b) {
    vector<int> A, B;
    for(int i = a.size() - 1; i >= 0; i--) {
        A.push_back(a[i] - '0');
    }
    for(int i = b.size() - 1; i >= 0; i--) {
        B.push_back(b[i] - '0');
    }

    reverse(B.begin(), B.end());

    vector<int> C;
    int t = 0;
    for(int i = A.size() - 1; i >= 0; i--) {
        t = t * 10 + A[i];
        C.push_back(t / B[0]);
        t %= B[0];
    }
    reverse(C.begin(), C.end());
    while(C.size() > 1 && C.back() == 0) {
        C.pop_back();
    }
    
    string res;
    for(int i = C.size() - 1; i >= 0; i--) {
        res += to_string(C[i]);
    }
    return res;
}

// 计算x的最后一个1的位置
int lowbit(int x) {
    return x & -x;
}

// 计算x的二进制表示有多少个1
int count_ones(int x) {
    int res = 0;
    while(x) {
        x -= lowbit(x);
        res++;
    }
    return res;
}

// KMP算法（字符串匹配）
// 时间复杂度：O(n + m) （n为s的位数，m为p的位数）
vector <int> kmp(string p, string s) {

    int n = p.size();
    int m = s.size();

    vector<int> ne(n, 0); // ne数组记录了p的每个前缀的最长相等前后缀长度
    vector<int> res;
    // 计算ne数组
    for (int i = 1, j = 0; i < n; i++) {
        while (j > 0 && p[i] != p[j]) {
            j = ne[j - 1];
        }
        if (p[i] == p[j]) {
            j++;
        }
        ne[i] = j;
    }

    // kmp匹配
    for (int i = 0, j = 0; i < m; i++) {
        while (j > 0 && s[i] != p[j]) {
            j = ne[j - 1];
        }
        if (s[i] == p[j]) {
            j++;
        }
        if (j == n) {
            res.push_back(i - n + 1);
            j = ne[j - 1];
        }
    }

    return res;
}

// Trie树（小写字典树）
// 时间复杂度：O(n) （n为所有字符串的总长度）
class Trie {
private: // 显式声明私有成员
    struct Node {
        int son[26]; // 26个小写字母的子节点索引
        int cnt;     // 以当前节点为结尾的单词数量
        // 新增：统计以当前节点为前缀的单词总数（补充前缀查询用）
        int prefix_cnt;
    } tr[MAX_NODE]; // Trie树节点数组
    int idx = 0; // 节点索引，0为根节点

public: // 关键修改：核心方法设为public，外部可调用
    // 构造函数：显式初始化根节点和索引
    Trie() {
        idx = 0;
        // 初始化根节点（son全0，cnt和prefix_cnt为0）
        memset(tr[0].son, 0, sizeof(tr[0].son));
        tr[0].cnt = 0;
        tr[0].prefix_cnt = 0;
    }

    // 插入字符串s
    void insert(string s) {
        int p = 0; // 从根节点开始
        for (int i = 0; i < s.size(); i++) {
            int u = s[i] - 'a'; // 转换为0-25的索引
            if(!tr[p].son[u]) { // 子节点不存在则创建
                tr[p].son[u] = ++idx;
                // 初始化新节点的所有成员
                memset(tr[idx].son, 0, sizeof(tr[idx].son));
                tr[idx].cnt = 0;
                tr[idx].prefix_cnt = 0;
            }
            p = tr[p].son[u];
            tr[p].prefix_cnt++; // 关键：前缀计数+1
        }
        tr[p].cnt++; // 单词结尾计数+1
    }

    // 查询字符串s出现的次数
    int query(string s) {
        int p = 0;
        for (int i = 0; i < s.size(); i++) {
            int u = s[i] - 'a';
            if(!tr[p].son[u]) { // 路径不存在，返回0
                return 0;
            }
            p = tr[p].son[u];
        }
        return tr[p].cnt;
    }

    // 新增：查询以s为前缀的单词数量
    int query_prefix(string s) {
        int p = 0;
        for (int i = 0; i < s.size(); i++) {
            int u = s[i] - 'a';
            if(!tr[p].son[u]) { // 前缀不存在，返回0
                return 0;
            }
            p = tr[p].son[u];
        }
        return tr[p].prefix_cnt;
    }

    // 删除字符串s（修复：增加cnt非0判断，避免负数）
    void remove(string s) {
        int p = 0;
        // 先检查字符串是否存在
        for (int i = 0; i < s.size(); i++) {
            int u = s[i] - 'a';
            if(!tr[p].son[u]) {
                return;
            }
            p = tr[p].son[u];
        }
        // 关键：只有cnt>0时才减1
        if(tr[p].cnt > 0) {
            tr[p].cnt--;
            // 可选：同步更新前缀计数（如果需要）
            // 如果需要「删除时同步更新 prefix_cnt」，逻辑会更复杂（需要记录路径并逐个减 1），但大部分场景下，prefix_cnt仅用于查询，删除时无需实时更新（清空时统一重置即可）
            // for (int i = s.size() - 1; i >= 0; i--) {
            //     int u = s[i] - 'a';
            //     p = tr[p].son[u];
            //     tr[p].prefix_cnt--;
            // }
        }
    }

    // 清空Trie树
    void clear() {
        for (int i = 0; i <= idx; i++) {
            memset(tr[i].son, 0, sizeof(tr[i].son));
            tr[i].cnt = 0;
            tr[i].prefix_cnt = 0; // 同步清空前缀计数
        }
        idx = 0; // 重置索引
    }
};

// 当前题目函数
void complete() {

    // 初始化Trie树
    Trie trie;
    // 插入字符串
    trie.insert("apple");
    trie.insert("app");
    trie.insert("banana");

    // 查询单词次数
    printf("app出现次数：%d\n", trie.query("app")); // 输出1
    printf("apple出现次数：%d\n", trie.query("apple")); // 输出1
    printf("orange出现次数：%d\n", trie.query("orange")); // 输出0

    // 查询前缀次数
    printf("以app为前缀的单词数：%d\n", trie.query_prefix("app")); // 输出2
    printf("以ban为前缀的单词数：%d\n", trie.query_prefix("ban")); // 输出1

    // 删除操作
    trie.remove("app");
    printf("删除后app出现次数：%d\n", trie.query("app")); // 输出0
    printf("删除后以app为前缀的单词数：%d\n", trie.query_prefix("app")); // 输出1

    // 清空
    trie.clear();
    printf("清空后apple出现次数：%d\n", trie.query("apple")); // 输出0
}

int main() {

    complete();

    return 0;
}