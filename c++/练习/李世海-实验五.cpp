#include<iostream>
using namespace std;
const int N = 100010;
struct Student{
    string numble;
    string name;
    int study;};
Student stu_arr[N];
int head, e[N], ne[N], idx;
void init(){
    head = -1;
    idx = 0;}

void add_to_head(string s_numble, string s_name, int s_study){
    stu_arr[idx].numble = s_numble;
    stu_arr[idx].name = s_name;
    stu_arr[idx].study = s_study;
    ne[idx] = head;
    head = idx;
    idx++;}

void add_to_tail(string s_numble, string s_name, int s_study){
    int tail = head;{
        while(ne[tail]!= -1){
        tail = ne[tail];}}
    stu_arr[idx].numble = s_numble;
    stu_arr[idx].name = s_name;
    stu_arr[idx].study = s_study;
    ne[idx] = ne[tail];
    ne[tail] = idx;
    idx++;}
int main()
{
    cout << "软件24-1 李世海" << endl;
    init();
    
    string s_numble;
    string s_name;
    int s_study;
    cin >> s_numble >> s_name >> s_study;
    
    add_to_head(s_numble, s_name, s_study);

    while(1)
    {
        cin >> s_numble;
        if(s_numble == "0") break;
        else{
            cin >> s_name >> s_study;
            add_to_tail(s_numble, s_name, s_study);}
    }

    for(int i = head; i != -1; i = ne[i]) cout << stu_arr[i].numble << " " << stu_arr[i].name << " " << stu_arr[i].study << endl;;
    cout << endl;


    return 0;
}