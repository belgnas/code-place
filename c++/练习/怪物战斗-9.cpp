// 太不容易了：终于找到边界数据了
// 5
// 50 111
// 10 111
// 1000 1
// 500 111
// 50 666

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 4010;

struct guaiwu
{
    int hp;
    int atk;
};

guaiwu arr[N];
int n; // 当前怪物数量 
int num = 0;

bool idea(guaiwu g1, guaiwu g2)
{
    if(g1.atk != g2.atk)
    {
        return g1.atk > g2.atk; // 优先消灭攻击力高的
    }
    else
    {
        return g1.hp > g2.hp; // 再考虑血量高的
    }
}

int main()
{
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> arr[i].hp >> arr[i].atk;
    }
    
    sort(arr, arr + n, idea);
    
    cout << "初始：" << endl;
    for(int i = 0; i < n; i++)
    {
        cout << arr[i].hp << " " << arr[i].atk << endl;
    }
    
    int sum_num = n;
    int xier = 0;
    while(xier < n)
    {
        if(arr[xier].hp <= 0)
        {
            xier++;
            continue;
        }
        arr[xier].hp = 0;
        for(int i = xier + 1; i < n; i++)
        {
            arr[i].hp -= arr[xier].atk;
        }
        cout << "当xier 击杀了 " << xier << endl;
        num++;
        for(int i = 0; i < n; i++)
        {
            cout << arr[i].hp << " " << arr[i].atk << endl;
        }
        
        
        
        while(arr[xier + 1].hp > 0 && xier < n)
        {
            for(int k = sum_num - 1; k > xier; k--)
            {
                if(arr[k].hp <= 0)
                {
                    cout << k << "爆炸" << endl;;
                    cout << arr[k].hp << "小于 0" << endl;
                    sum_num--;
                    for(int i = xier; i <= k; i++)
                    {
                        arr[i].hp -= arr[k].atk;
                    }
                    cout << "当xier 击杀了 " << xier << " 并且这时候第" << k << "爆炸后" << endl;
                    for(int i = 0; i < n; i++)
                    {
                        cout << arr[i].hp << " " << arr[i].atk << endl;
                    }

                }
            }
        }
        
        xier++;
        
        
    }
    
    cout << "结束：" << xier << endl;
    for(int i = 0; i < n; i++)
    {
        cout << arr[i].hp << " " << arr[i].atk << endl;
    }
    
    cout << num << endl;
    
    
    
    return 0;
}