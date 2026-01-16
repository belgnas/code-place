#include<iostream>
#include<string>
using namespace std;

const int N = 20 + 5;
int n;
string stu_name;
int stu_num, stu_score_1, stu_score_2, stu_score_3;

struct Students
{
    int num;
    string name;
    int score_1;
    int score_2;
    int score_3;
};

struct Students stu[N];

void input()
{
    stu[stu_num].num = stu_num;
    stu[stu_num].name = stu_name;
    stu[stu_num].score_1 = stu_score_1;
    stu[stu_num].score_2 = stu_score_2;
    stu[stu_num].score_3 = stu_score_3;
}

void print()
{
    for(int i = 1; i < N; i++)
    {
        if(stu[i].num == 0) continue;
        cout << stu[i].num << " "
            << stu[i].name << " "
            << stu[i].score_1 << " "
            << stu[i].score_2 << " "
            << stu[i].score_3 << " "
            << endl;
    } 
}

int main()
{
    cout << "软件24-1 李世海" << endl;
    
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> stu_num >> stu_name >> stu_score_1 >> stu_score_2 >> stu_score_3;
        input();
    }
    
    print();
    
    return 0;
}