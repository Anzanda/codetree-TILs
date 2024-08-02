#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int a, b, c, d, e;
    cin >> a >> b >> c >> d >> e;

    vector<int> ans;
    ans.push_back(a > b ? 1 : 0);
    ans.push_back(a > c ? 1 : 0);
    ans.push_back(a > d ? 1 : 0);
    ans.push_back(a > e ? 1 : 0);

    for(auto a : ans ) {
        cout<< ans << endl;
    }
    return 0;
}