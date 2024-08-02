#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
using pii = pair<int,int>;

const int MAX = 1e2 +7;

int n;
pii s[MAX];
pii t[MAX];
int main() {
    // 여기에 코드를 작성해주세요.
    cin >> n;
    for(int i=1; i<=n; i++) {
        int ss, tt, bb;
        cin >> ss >> tt >> bb;
        s[i] = pii(ss, bb);
        t[i] = pii(tt, bb);
    }
    sort(s+1, s+n+1);
    sort(t+1, t+n+1);

    int ans = 0;
    int si = 1;
    int ti = 1;
    int used = 0;
    for(int i=1; i<=1000; i++) {
        if(s[si].first == i) {
            used += s[si].second;
            si++;
        }
        if(t[ti].first == i) {
            used -= t[ti].second;
            ti++;
        }
        
        ans = max(ans, used);
    }
    cout << ans << endl;
    return 0;
}