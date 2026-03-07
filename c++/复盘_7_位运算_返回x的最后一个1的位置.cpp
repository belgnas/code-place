#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

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

// 当前题目函数
void complete() {
    int x;
    cin >> x;
    // 计算x的最后一个1的位置
    int ans = lowbit(x);
    cout << ans << endl;
}

int main() {

    complete();

    return 0;
}