#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int a, b;
    cin >> a >> b;
    if(a > b) {
        cout << a*b << endl;
     } else {
        cout << (b/a) << endl;
     }
    return 0;
}