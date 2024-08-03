#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

const int MAX = 70+7;

//612
int n, m, k;
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};
bool vst[MAX][MAX];
bool is_range(int r, int c) {
    return r>=0 && r<= n && c >= 1 && c <= m;
}
bool is_valid(int r, int c) {
    if(!is_range(r, c)) return false;
    if(vst[r][c]) return false;
    for(int i=0; i<4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(nr < 0) continue;
        if(!is_range(nr, nc)) return false;
        if(vst[nr][nc]) return false;
    }
    return true;
}
int ans;
int tmp_ans;
bool vst2[MAX][MAX];
void dfs(int r, int c) {
    vst2[r][c] = true;

    tmp_ans = max(tmp_ans, r);
    for(int i=0; i<4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(!is_range(nr, nc)) continue;
        if(!vst[nr][nc]) continue;
        if(vst2[nr][nc]) continue;
        dfs(nr, nc);
    }
}
void run() {
    int c, d;
    cin >> c >> d;

    int r = 0;
    if(vst[r+1][c]) {
       if(is_range(r, c-2) && (!vst[r+1][c-1])) {
        c -= 1;
        d = (d-1)%4;
       }
       else if(is_range(r, c+2) && (!vst[r+1][c+1])) {
         c += 1;
         d = (d+1)%4;
       }
       else {
        memset(vst, false, sizeof vst);
        return;
       }
    }
    
    // r == 0
    bool alive = true;
    while(alive) {
        // 1
        if(is_valid(r+1, c)) {
            r++;
            continue;
        }
        // 2
        if(is_valid(r, c-1) && is_valid(r+1, c-1)) {
            r++;
            c--;
            d = (d-1)%4;
            continue;
        }
        if(is_valid(r, c+1) && is_valid(r+1, c+1)) {
            r++;
            c++;
            d = (d+1)%4;
            continue;
        }
        alive = false;
    }
    if(r-1 < 1) {
        memset(vst, false, sizeof vst);
        return;
    }

    tmp_ans = r+1;
    memset(vst2, false, sizeof vst2);
    dfs(r+dr[d], c+dc[d]);
    ans += tmp_ans;
    vst[r][c] = true;
    for(int i=0; i<4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        vst[nr][nc] = true;
    }
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> k;

    while(k--) {
        run();
    }
    cout << ans << endl;
    // 여기에 코드를 작성해주세요.
    return 0;
}