#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// 怪物结构体
struct guaiwu
{
    int hp;
    int atk;
};

// 定义怪物数组和怪物数量
guaiwu arr[4010];
int n;

// 排序函数，优先按自爆伤害从小到大，若相同则按血量从小到大
bool idea(guaiwu g1, guaiwu g2)
{
    if (g1.atk != g2.atk)
    {
        return g1.atk < g2.atk;
    }
    return g1.hp < g2.hp;
}

int main()
{
    cin >> n;
    int totalDamage = 0;
    // 输入怪物信息并计算总自爆伤害
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i].hp >> arr[i].atk;
        totalDamage += arr[i].atk;
    }

    int count = 0;
    int validNum = 0;
    queue<int> q;
    q.push(0);

    // 找出无法被炸死的怪物
    for (int i = 0; i < n; i++)
    {
        if (arr[i].hp > totalDamage - arr[i].atk)
        {
            count++;
            q.back() += arr[i].atk;
        }
        else
        {
            arr[validNum++] = arr[i];
        }
    }

    // 处理连环爆炸
    while (!q.empty())
    {
        int dmg = q.front();
        q.pop();
        int newValid = 0;
        for (int i = 0; i < validNum; i++)
        {
            arr[i].hp -= dmg;
            if (arr[i].hp <= 0)
            {
                q.push(arr[i].atk);
            }
            else
            {
                arr[newValid++] = arr[i];
            }
        }
        validNum = newValid;
    }

    // 循环处理剩余怪物
    while (validNum > 0)
    {
        count++;
        sort(arr, arr + validNum, idea);
        q.push(arr[validNum - 1].atk);
        validNum--;

        while (!q.empty())
        {
            int dmg = q.front();
            q.pop();
            int newValid = 0;
            for (int i = 0; i < validNum; i++)
            {
                arr[i].hp -= dmg;
                if (arr[i].hp <= 0)
                {
                    q.push(arr[i].atk);
                }
                else
                {
                    arr[newValid++] = arr[i];
                }
            }
            validNum = newValid;
        }
    }

    cout << count << endl;
    return 0;
}