#include <iostream>
#include <string>
#include <vector>
using namespace std;

const vector<vector<string>> T = {{"***",".*."}, {".*.", "***"}, {"*.", "**", "*."}, {".*", "**", ".*"}};
const vector<vector<string>> L = {{"***", "..*"}, {"***", "*.."}, {"*..", "***"}, {"..*", "***"}, {"*.", "*.", "**"}, {".*", ".*", "**"}, {"**", "*.", "*."}, {"**", ".*", ".*"}};

bool test_T(int i, int j, vector<string>& srr) {

    for (const auto& pattern : T) {
        int pat_rows = pattern.size();
        int pat_cols = pattern[0].size();
        
        // 边界检查
        if (i + pat_rows > srr.size() || j + pat_cols > srr[0].size()) {
            continue;
        }
        
        bool match = true;
        for (int r = 0; r < pat_rows && match; r++) {
            for (int c = 0; c < pat_cols && match; c++) {
                if (pattern[r][c] != srr[i + r][j + c]) {
                    match = false;
                }
            }
        }
        
        if (match) {
            return true;
        }
    }
    return false;
}

bool test_L(int i, int j, vector<string>& srr) {
    for (const auto& pattern : L) {
        int pat_rows = pattern.size();
        int pat_cols = pattern[0].size();
        
        if (i + pat_rows > srr.size() || j + pat_cols > srr[0].size()) {
            continue;
        }
        
        bool match = true;
        for (int r = 0; r < pat_rows && match; r++) {
            for (int c = 0; c < pat_cols && match; c++) {
                if (pattern[r][c] != srr[i + r][j + c]) {
                    match = false;
                }
            }
        }
        
        if (match) {
            return true;
        }
    }
    return false;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<string> srr(n);
        for (int i = 0; i < n; i++) {
            cin >> srr[i];
        }
        
        bool found = false;
        for (int i = 0; i < n && !found; i++) {
            for (int j = 0; j < n && !found; j++) {
                if (test_T(i, j, srr)) {
                    cout << "T" << endl;
                    found = true;
                } else if (test_L(i, j, srr)) {
                    cout << "L" << endl;
                    found = true;
                }
            }
        }
    }
    return 0;
}