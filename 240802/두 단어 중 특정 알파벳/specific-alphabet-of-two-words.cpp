#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int n;
vector<pair<string, string>> a;
int main() {
    cin >> n;
    a.push_back(make_pair("", ""));
    for(int i=1; i<=n; i++) {
        string s1, s2;
        cin >> s1 >> s2;
        a.push_back(make_pair(s1, s2));
    }
    for(char c='a'; c<='z'; c++) {
        int ans = 0;
        for(int i=1; i<=n; i++) {
            string s1 = a[i].first;
            string s2 = a[i].second;
            
            int a1 = 0;
            for(auto c1 : s1) {
                if(c == c1) {
                    a1++;
                }
            }
            int a2 = 0;
            for(auto c2: s2) {
                if(c == c2) {
                    a2++;
                }
            }
            ans += max(a1, a2);
        }
        cout << ans << endl;
    }
    return 0;
}