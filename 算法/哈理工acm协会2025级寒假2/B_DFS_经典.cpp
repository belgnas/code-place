#include <iostream>
#include <vector>
using namespace std;

bool test(vector<vector<int>> &arr, int x, int y) {
    bool flat = false;
    if (hang(arr, x) && lie(arr, y) && xie(arr, x, y)) {
        flat = true;
    }
    return flat;
}

bool hang(vector<vector<int>> &arr, int x) {
    bool flat = true;
    for (int j = 0; j < arr.size(); j++) {
        if (arr[x][j] == 1) {
            flat = false;
            break;
        }
    }
    return flat;
}

bool lie(vector<vector<int>> &arr, int y) {
    bool flat = true;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i][y] == 1) {
            flat = false;
            break;
        }
    }
    return flat;
}

bool xie(vector<vector<int>> &arr, int x, int y) {
    bool flat = true;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[x][y] = 1) {
            flat = false;
            break;
        }
        x = (x + 1) % arr.size();
        y = (y + 1) % arr.size();
    }
    return flat;
}

void dfs(vector<vector<int>> &arr, vector<pair<int, int>> &ans, int n) {
    if (ans.size() == n) {
        for (int i = 0; i < n; i++) {
            cout << ans[i].first << ' ';
        }
        cout << endl;
        for (int i = 0; i < n; i++) {
            cout << ans[i].second << ' ';
        }
        cout << endl;

        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (test(arr, i, j) == true) {
                arr[i][j] = 1;
                ans.push_back(<i, j>);
                dfs(arr, ans, n);
                arr[i][j] = 0;
                ans.pop_back();
            }
        }
    }
}

int main() {

    int n;
    cin >> n;
    
    vector<vector<int>> arr(n, vector<int> (n, 0));
    vector<pair<int, int>> ans; 
    dfs(arr, ans, n);

    return 0;
}