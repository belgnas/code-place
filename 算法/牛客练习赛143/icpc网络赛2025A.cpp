#include<bits/stdc++.h>
using namespace std;

struct team
{
    string teamname = "";
    char problemid = '0';
    int time = 0;
    string result = "";
};

struct aftericpc
{
    string teamname = "";
    int use_time = 0;    // 总用时（含罚时）
    int pass_min = 0;    // 通过题目数
    vector<pair<bool, int>> pass_problem; // <是否通过，累计用时（含罚时）>

    // 构造函数：初始化26个题目（A-Z）的默认状态
    aftericpc() : pass_problem(26, {false, 0}) {}
};

// 快速查找队伍在after数组中的索引
int quick_find(const string &name, const vector<aftericpc> &after)
{
    for(int i = 0; i < int(after.size()); i++)
    {
        if(after[i].teamname == name)
        {
            return i;
        }
    }
    return -1; // 理论上不会触发（队伍名已去重）
}

// 函数：根据给定的场景（是否将Unknown视为通过），计算各队伍的最终状态
vector<aftericpc> calculate_scene(const vector<team> &icpc, const set<string> &name_set, bool unknown_as_pass)
{
    int team_cnt = name_set.size();
    vector<aftericpc> after(team_cnt);

    // 初始化队伍名
    int idx = 0;
    for(const auto &team_name : name_set)
    {
        after[idx++].teamname = team_name;
    }

    // 第一步：处理Accepted/Rejected（两种场景通用）
    for(const auto &rec : icpc)
    {
        if(rec.result == "Unknown") continue; // 场景2中Unknown后续不处理，场景1后续单独处理

        int team_idx = quick_find(rec.teamname, after);
        int problem_idx = rec.problemid - 'A';

        // 已通过的题目跳过（无论哪种结果）
        if(after[team_idx].pass_problem[problem_idx].first)
        {
            continue;
        }

        if(rec.result == "Rejected")
        {
            // 拒绝：加20罚时，不标记通过
            after[team_idx].pass_problem[problem_idx].second += 20;
        }
        else if(rec.result == "Accepted")
        {
            // 通过：标记通过，总用时=提交时间+累计罚时
            after[team_idx].pass_problem[problem_idx].first = true;
            after[team_idx].pass_problem[problem_idx].second += rec.time;
        }
    }

    // 第二步：处理Unknown（根据场景决定是否视为通过）
    if(unknown_as_pass)
    {
        for(const auto &rec : icpc)
        {
            if(rec.result != "Unknown") continue;

            int team_idx = quick_find(rec.teamname, after);
            int problem_idx = rec.problemid - 'A';

            if(after[team_idx].pass_problem[problem_idx].first)
            {
                continue; // 已通过（Accepted或之前的Unknown处理）
            }

            // Unknown视为通过：标记通过，总用时=提交时间+累计罚时
            after[team_idx].pass_problem[problem_idx].first = true;
            after[team_idx].pass_problem[problem_idx].second += rec.time;
        }
    }

    // 第三步：计算每个队伍的总通过数和总用时
    for(auto &team : after)
    {
        int total_pass = 0;
        int total_time = 0;
        for(const auto &prob : team.pass_problem)
        {
            if(prob.first)
            {
                total_pass++;
                total_time += prob.second;
            }
        }

        team.pass_min = total_pass;
        team.use_time = total_time;
    }

    return after;
}

// 函数：从场景结果中筛选出冠军队伍（通过数最多，用时最少）
set<string> get_champions(const vector<aftericpc> &after)
{
    set<string> champions;
    if(after.empty()) return champions;

    // 找到最大通过数和对应的最小用时
    int max_pass = 0;
    int min_time = INT_MAX;
    for(const auto &team : after)
    {
        if(team.pass_min > max_pass)
        {
            max_pass = team.pass_min;
            min_time = team.use_time;
        }
        else if(team.pass_min == max_pass && team.use_time < min_time)
        {
            min_time = team.use_time;
        }
    }

    // 收集所有符合“最大通过数+最小用时”的队伍（可能有多个并列冠军）
    for(const auto &team : after)
    {
        if(team.pass_min == max_pass && team.use_time == min_time)
        {
            champions.insert(team.teamname);
        }
    }

    return champions;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        vector<team> icpc(n);
        for(int i = 0; i < n; i++)
        {
            cin >> icpc[i].teamname >> icpc[i].problemid >> icpc[i].time >> icpc[i].result;
        }

        // 1. 队伍名去重（所有场景共用同一批队伍）
        set<string> name_set;
        for(const auto &rec : icpc)
        {
            name_set.insert(rec.teamname);
        }

        // 2. 计算两种场景的队伍状态
        vector<aftericpc> scene1 = calculate_scene(icpc, name_set, true);  // 场景1：Unknown视为通过
        vector<aftericpc> scene2 = calculate_scene(icpc, name_set, false); // 场景2：Unknown视为不通过

        // 3. 分别获取两种场景的冠军队伍
        set<string> champ_scene1 = get_champions(scene1);
        set<string> champ_scene2 = get_champions(scene2);

        // 4. 合并两种场景的冠军（并集，去重）
        set<string> all_possible_champs;
        for(const auto &name : champ_scene1)
        {
            all_possible_champs.insert(name);
        }
        for(const auto &name : champ_scene2)
        {
            all_possible_champs.insert(name);
        }

        // 5. 输出所有有可能获胜的队伍（按字典序，set自带排序）
        for(auto it = all_possible_champs.begin(); it != all_possible_champs.end(); it++)
        {
            if(it != all_possible_champs.begin())
            {
                cout << " ";
            }
            cout << *it;
        }
        cout << "\n";
    }

    return 0;
}