#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int a;
    cin >> a;

    if(a%3 == 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    if(a%5 == 0) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}