#include <iostream>
#include <vector>
using namespace std;

void dfs(vector<bool> &choose, vector<int> &ans, int n) {
    if (ans.size() == n) {
        for (int i = 0; i < n; i++) {
            cout << ans[i] << ' ';
        }
        cout << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        if (choose[i] == false) {
            choose[i] = true;
            ans.push_back(i + 1);
            dfs(choose, ans, n);

            choose[i] = false;
            ans.pop_back();
        }
    }
}

int main() {

    int n;
    cin >> n;

    vector<bool> choose(n, false);
    vector<int> ans;

    dfs(choose, ans, n);


    return 0;
}