#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr)

#define int long long

struct Team{
    vector<bool> answer;
    vector<int> used_time;
    int final_solve;
    int final_time;
};

signed main() {
    
    IOS;

    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<Team> teams(n + 1, {vector<bool> (m, false), vector<int> (m, 0), 0, 0});
        for (int i = 0; i < k; i++) {
            int idx;
            char problem;
            int time;
            string status;
            cin >> idx >> problem >> time >> status;
            if (teams[idx].answer[problem - 'A'] == true) {
                continue;
            }
            else {
                if (status == "Correct") {
                    teams[idx].answer[problem - 'A'] = true;
                    teams[idx].used_time[problem - 'A'] += time;
                    teams[idx].final_solve++;
                    teams[idx].final_time += teams[idx].used_time[problem - 'A'];
                }
                else {
                    teams[idx].used_time[problem - 'A'] += 20;
                }
            }
        }

        int rank_1 = 1;
        for (int i = 1; i <= n; i++) {
            if (teams[i].final_solve > teams[1].final_solve) {
                rank_1 ++;
            }
            if (teams[i].final_solve == teams[1].final_solve && teams[i].final_time < teams[1].final_time) {
                rank_1 ++;
            }
        }

        // cout << rank_1 << endl;

        int G = (n + 9) / 10;
        if ( G + 1 <= rank_1 && rank_1 <= 3 * G) {
            cout << "cos" << endl;
        }
        else {
            cout << "kexi" << endl;
        }
        
    }


    return 0;
}