#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
using pii = pair<int,int>;
const int MAX = 70+7;


int n, m, k;
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};
int golem[MAX][MAX];
bool is_exit[MAX][MAX];
bool is_golem_range(int r, int c) {
    return r >= -1 && r <= n-1 && c >= 2 && c <= m-1;
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
        if(golem[nr][nc] != -1) return false;
    }    
    return true;
}
int ans;
int tmp_ans;
bool vst[MAX][MAX];
bool is_range(int r, int c) {
    return r>=1 && r<=n && c>=1 && c<=m;
}
// void dfs(int r, int c) {
//     vst[r][c] = true;
//     tmp_ans = max(tmp_ans, r);
//     for(int i=0; i<4; i++) {
//         int nr = r + dr[i];
//         int nc = c + dc[i];
//         if(!is_range(nr, nc)) continue;
//         if(!golem[nr][nc]) continue;
//         if(vst[nr][nc]) continue;
//         dfs(nr, nc);
//     }
// }
void run() {
    int r, c, d;
    cin >> c >> d;

    r = -1;
    
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
        memset(golem, -1, sizeof golem);
        memset(is_exit, false, sizeof is_exit);
        return;
    }


    tmp_ans = r + 1;

    golem[r][c] = k;
    for(int i=0; i<4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        golem[nr][nc] = k;
    }
    is_exit[r+dr[d]][c+dc[d]] = true;

    memset(vst, false, sizeof vst);
    queue<pii> q;
    q.push(pii(r, c));
    while(q.size()) {
        auto [rr, cc] = q.front();
        q.pop();

        vst[rr][cc] = true;
        tmp_ans = max(tmp_ans, rr);
        for(int i=0;  i<4; i++) {
            int nr = rr + dr[i];
            int nc = cc + dc[i];
            if(!is_range(nr, nc)) continue;
            if(vst[nr][nc]) continue;
            if((golem[rr][cc] == golem[nr][nc]) || (is_exit[rr][cc] && golem[nr][nc] != -1)) 
                q.push(pii(nr, nc));
        }
    }
    
    // printf("tmp_ans: %d\n", tmp_ans);
    // printf("r: %d, c: %d\n", r, c);
    ans += tmp_ans;

  
    
}
int main(void) {
    cin >> n >> m >> k;
    memset(golem, -1, sizeof golem);
    while(k--) {
        run();
    }

    cout << ans << endl;
}