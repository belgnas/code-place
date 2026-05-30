#include <iostream>
#include <vector>

using namespace std;

// 快速排序模板
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

// 打印数组（末尾换行）
void print_arr(vector<int> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1) cout << ' ';
        else cout << endl;
    }
}

// 当前题目函数
void complete() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    quick_sort(arr);
    
    print_arr(arr);
}

int main() {

    complete();

    return 0;
}