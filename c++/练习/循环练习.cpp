#include <iostream>
using namespace std;
class Virus {
    public: 
        Virus() {
            cout << "I am the ancestor of the new virus!" << endl;
        }
        ~Virus() {
            cout << "I must disappear!" << endl;
        } 
        virtual void eat() = 0; //定义纯虚函数 
};
class vOne : public Virus
{
    public: 
        vOne() {
            cout << "vOne is born." << endl;
        }
        ~vOne() {
            cout << "vOne is dead." << endl;
        }
        void eat() {
            cout << "vOne is living in your body." << endl;
        }
};
class vTwo : public Virus
{
    public: 
        vTwo() {
            cout << "vTwo is born." << endl;
        }
        ~vTwo() {
            cout << "vTwo is dead." << endl;
        }
        void eat() {
            cout << "vTwo is living in your body." << endl;
        }
};

int main() {
    Virus *v;     //定义父类指针v 
    vOne v1;     //定义vOne对象v1 
    vTwo v2;     //定义vTwo对象v2 
    v = &v1;
    v->eat(); //通过父类指针调用eat()方法 
    v = &v2;
    v->eat(); //通过父类指针调用eat()方法 
    
    cout << "Our immune system is kill v1 and v2..." << endl;
    return 0;
} 