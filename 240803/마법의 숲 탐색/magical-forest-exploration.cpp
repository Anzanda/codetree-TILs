#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

const int MAX = 70+7;


int n, m, k;
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};
int golem[MAX][MAX];
bool is_golem_range(int r, int c) {
    return r >= 0 && r <= n-1 && c >= 2 && c <= m-1;
}
bool can_alive(int r, int c) {
    return r >= 2 && r <= n-1 && c >= 2 && c <= m-1;
}
bool is_valid(int r, int c) {
    if(!is_golem_range(r, c)) return false;
    for(int i=0; i<4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(nr <= -1) continue;
        if(golem[nr][nc]) return false;
    }    
    return true;
}
int ans;
int tmp_ans;
bool vst[MAX][MAX];
bool is_range(int r, int c) {
    return r>=1 && r<=n && c>=1 && c<=m;
}
void dfs(int r, int c) {
    vst[r][c] = true;
    tmp_ans = max(tmp_ans, r);
    for(int i=0; i<4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(!is_range(nr, nc)) continue;
        if(!golem[nr][nc]) continue;
        if(vst[nr][nc]) continue;
        dfs(nr, nc);
    }
}
void run() {
    int r, c, d;
    cin >> c >> d;

    r = 0;
    
    bool alive = true;
    while(alive) {
        if(is_valid(r+1, c)) {
            r++;
            continue;
        }
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

    if(!can_alive(r, c)) {
        memset(golem, false, sizeof golem);
        return;
    }


    tmp_ans = r + 1;

    memset(vst, false, sizeof vst);
    dfs(r + dr[d], c + dc[d]);
    
    ans += tmp_ans;
    
    golem[r][c] = true;
    for(int i=0; i<4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        golem[nr][nc] = true;
    }
    
}
int main(void) {
    cin >> n >> m >> k;
    while(k--) {
        run();
    }

    cout << ans << endl;
}