/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <tuple>
#include <cstring>
#include <queue>
#define endl '\n'
using namespace std;
using pii = pair<int,int>;

const int MAXN = 70+7;
const int MAXK = 1000+7;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

int ans;

int n, m, k;
int c[MAXK];
int d[MAXK];
int vst[MAXN][MAXN];
bool is_exit[MAXN][MAXN];
bool is_range(int r, int c) {
    return r>=1&&r<=n&&c>=1&&c<=m; // r은 0부터?
}
bool can_move(int r, int c) { // -1부터 시작...
    if(vst[r][c]) return false;
    if(c == 1 || c == m) return false; // 골렘의 중심!!
    
    for(int i=0; i<4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(nr <= 0) continue;
        if(nc < 1 || nc > m) return false;
        if(!is_range(nr, nc)) return false;
        if(vst[nr][nc]) return false;
    }
    return true;
}
bool can_move_down(int r, int c) {
    if(!can_move(r, c)) {
        return false;
    }
    if(!can_move(r+1, c)) {
        return false;
    }
    return true;
}
bool can_move_left(int r, int c) {
    if(!can_move(r, c)) {
        return false;
    }
    if(!can_move(r, c-1)) {
        return false;
    }
    if(!can_move(r+1, c-1)) {
        return false;
    }
    return true;
}
bool can_move_right(int r, int c) {
    if(!can_move(r, c)) {
        return false;
    }
    if(!can_move(r, c+1)) {
        return false;
    }
    if(!can_move(r+1, c+1)) {
        return false;
    }
    return true;
}
pii loc;
int exit_dir; // 북 동 남 서
bool move() {
    int r, c; tie(r, c) = loc;
    if(can_move_down(r, c)) {
        loc = pii(r+1, c);
        return true;
    }
    if(can_move_left(r, c)) {
        loc = pii(r+1, c-1);
        exit_dir = (exit_dir+4-1)%4;
        return true;
    }
    if(can_move_right(r, c)) {
        loc = pii(r+1, c+1);
        exit_dir = (exit_dir+4+1)%4;
        return true;
    }
    return false;
}
bool is_finished() {
    int r, c; tie(r, c) = loc;
    for(int i=0; i<4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(!is_range(nr, nc)) {
            return true;
        }
    }
    return false;
}
void settle_down(int curr) {
    int r, c; tie(r, c) = loc;
    vst[r][c] = curr;
    for(int i=0; i<4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        vst[nr][nc] = curr;
        if(i == exit_dir) {
            is_exit[nr][nc] = true;
        }
    }
}
int bfs() {
    int dist[MAXN][MAXN];
    memset(dist, -1, sizeof dist);
    
    int ret = -1;
    
    queue<pii> q;
    q.push(loc);
    dist[loc.first][loc.second] = 0;
    while(q.size()) {
        int r, c;
        tie(r, c) = q.front();
        q.pop();
        
        //printf("(%d, %d)\n", r, c);
        ret = max(ret, r);
        for(int i=0; i<4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(!is_range(nr, nc)) continue;
            if(dist[nr][nc] != -1) continue;
            if(!vst[nr][nc]) continue;
            if(vst[r][c] != vst[nr][nc]) {
                if(!is_exit[r][c]) continue; // 출구 아니면 못나가.
            } 
            dist[nr][nc] = dist[r][c] + 1;
            q.push(pii(nr, nc));
        }
    }
    
    return ret;
}
void print_current_golem(int curr) {
    int r, c;
    tie(r, c) = loc;
    printf("golem%d: (%d, %d) | ", curr, r, c);
    printf("exit_dir: %d\n", exit_dir);
}
void go(int curr) {
    loc = pii(-1, c[curr]);
    exit_dir = d[curr];
    while(move()) {
        // print_current_golem(curr);
    }
    
    if(is_finished()) {
        memset(vst, 0, sizeof vst);
        memset(is_exit, 0, sizeof is_exit);
        return;
    }
    settle_down(curr);
    ans += bfs();
}
int main()
{
    cin >> n >> m >> k;
    for(int i=1; i<=k; i++) {
        cin >> c[i] >> d[i];
    }
    for(int i=1; i<=k; i++) {
        go(i);
    }
    
    printf("%d\n", ans);
    return 0;
}