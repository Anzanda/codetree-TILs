#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int a, b, c;
    cin >> a >> b >> c;
    
    if(b > a && b < c) {
        cout << 1;
    } else {
        cout << 0;
    }
    return 0;
}