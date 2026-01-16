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
    int sum = 0;
    for(int i = 0; i < n; i++)
    {
        cin >> arr[i].hp >> arr[i].atk;
        sum += arr[i].atk;
    }

    int zhongshu = n;
    int chaohou_hp = 0;
    for(int i = 0; i < zhongshu; i++)
    {
        if(sum - arr[i].atk > 0)
        {
            arr[i].atk = arr[n].atk;
            arr[i].hp = arr[n].hp;
            chaohou_hp++;
            for(int j = 0; j < n; j++)
            {
                arr[j].hp -= arr[i].atk;
            }
            
        }
        
    }

    cout << "最初始：" << endl;
    for(int i = 0; i < n; i++)
    {
        cout << arr[i].hp << " " << arr[i].atk << endl;
    }
    
     
    sort(arr, arr + n, idea);
     
    cout << "初始：" << endl;
    for(int i = 0; i < n; i++)
    {
        cout << arr[i].hp << " " << arr[i].atk << endl;
    }
     
    int sum_num = n;
    int xier = 0;
    while(arr[xier].hp > 0)
    {
        arr[xier].hp = 0;
        for(int i = xier + 1; i < n; i++)
        {
            arr[i].hp -= arr[xier].atk;
        }
        cout << "当xier 击杀了 " << xier << endl;
        for(int i = 0; i < n; i++)
        {
            cout << arr[i].hp << " " << arr[i].atk << endl;
        }
         
         
         
        while(arr[sum_num - 1].hp <= 0 && arr[xier + 1].hp > 0 && xier < n)
        {
            cout << sum_num - 1 << "爆炸" << endl;;
            cout << arr[sum_num - 1].hp << "小于 0" << endl;
            sum_num--;
            for(int i = xier; i < sum_num; i++)
            {
                arr[i].hp -= arr[sum_num - 1].atk;
            }
            cout << "当xier 击杀了 " << xier << " 并且这时候第" << sum_num << "爆炸后" << endl;
            for(int i = 0; i < n; i++)
            {
                cout << arr[i].hp << " " << arr[i].atk << endl;
            }
        }
         
        xier++;
         
         
    }
     
    cout << "结束：" << xier << endl;
    for(int i = 0; i < n; i++)
    {
        cout << arr[i].hp << " " << arr[i].atk << endl;
    }
     
    cout << xier << endl;
     
     
     
    return 0;
}