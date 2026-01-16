#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
#include <cstring>
#include <set>
#include <tuple>

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'

const int QMX = 10000; // 最大时间点

// 电梯类：封装电梯的状态和行为
class Elevator
{
private:
    int currentFloor;       // 当前楼层
    int direction;          // 运行方向：1-向上，-1-向下，0-静止
    int orderSet;           // 待处理指令集合（位掩码）
    vector<int> timeOrders; // 每个时刻收到的指令

public:
    // 构造函数
    Elevator() : currentFloor(1), direction(0), orderSet(0), timeOrders(QMX + 1, 0) {}

    // 设置指定时刻的指令
    void setOrder(int time, int floor)
    {
        if (time >= 0 && time <= QMX)
        {
            timeOrders[time] = floor;
        }
    }

    // 模拟电梯运行，返回每个时刻的位置
    vector<int> simulate()
    {
        vector<int> positions(QMX + 1);

        for (int t = 0; t <= QMX; ++t)
        {
            // 记录当前时刻位置
            positions[t] = currentFloor;

            // 处理当前时刻的新指令
            int newOrder = timeOrders[t];
            if (newOrder != 0 && newOrder != currentFloor)
            {
                orderSet |= (1LL << newOrder);
            }

            // 清除当前楼层的指令（已到达）
            orderSet &= ~(1LL << currentFloor);

            // 判断是否存在更高/更低楼层的指令
            bool hasHigher = (orderSet >> currentFloor) > 0;
            bool hasLower = ((1LL << currentFloor) - 1) & orderSet;

            // 更新运行方向
            updateDirection(hasHigher, hasLower);

            // 移动到下一时刻的位置
            currentFloor += direction;
        }

        return positions;
    }

private:
    // 根据指令情况更新运行方向
    void updateDirection(bool hasHigher, bool hasLower)
    {
        if (direction >= 0)
        { // 上行或静止状态
            if (hasHigher)
            {
                direction = 1;
            }
            else if (hasLower)
            {
                direction = -1;
            }
            else
            {
                direction = 0;
            }
        }
        else
        { // 下行状态
            if (hasLower)
            {
                direction = -1;
            }
            else if (hasHigher)
            {
                direction = 1;
            }
            else
            {
                direction = 0;
            }
        }
    }
};

signed main()
{
    IOS;

    int T;
    cin >> T;
    while (T--)
    {
        int n, q;
        cin >> n >> q;

        // 创建电梯对象
        Elevator elevator;

        // 读取并设置指令
        for (int i = 0; i < n; ++i)
        {
            int ti, fi;
            cin >> ti >> fi;
            elevator.setOrder(ti, fi);
        }

        // 模拟电梯运行，获取所有时刻的位置
        vector<int> positions = elevator.simulate();

        // 处理查询
        for (int i = 0; i < q; ++i)
        {
            int Q;
            cin >> Q;
            cout << positions[Q] << '\n';
        }
    }

    return 0;
}
