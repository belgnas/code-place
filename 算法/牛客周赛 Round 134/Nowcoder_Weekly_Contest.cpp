#include <iostream>
using namespace std;
int main() {
    
    int x;
    cin >> x;
    if (x <= 1599) {
        cout << "Rated" << endl;
    }
    else {
        cout << "Unrated" << endl;
    }
    
    return 0;
}