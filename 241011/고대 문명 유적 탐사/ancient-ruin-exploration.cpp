/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <tuple>
#define endl '\n'
#define ff first
#define ss second
using namespace std;
using pii = pair<int,int>;

const int MAXN = 5+7;
const int MAXM = 300+7;

int dr[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
int dc[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

int n, k, m;
int a[MAXN][MAXN];
int t[MAXM];
bool is_range(int r, int c) {
    return r>=1&&r<=n&&c>=1&&c<=n;
}
bool compare(pair<int, pii> &a, pair<int, pii> &b) {
    if(a.ff != b.ff) {
        return a.ff < b.ff;
    }
    if(a.ss.ss != b.ss.ss) {
        return a.ss.ss < b.ss.ss;
    }
    return a.ss.ff < b.ss.ff;
}
void rotate_90(int r, int c) {
    int tmp[MAXN][MAXN];
    memcpy(tmp, a, sizeof tmp);
    for(int i=0; i<8; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        
        int nnr = r + dr[(i+2+8)%8];
        int nnc = c + dc[(i+2+8)%8];
        tmp[nnr][nnc] = a[nr][nc];
    }
    memcpy(a, tmp, sizeof tmp);
}
bool vst[MAXN][MAXN];
bool color[MAXN][MAXN];
int dfs(int r, int c) {
    int ret = 1;
    vst[r][c] = true;
    int dr[4] = {1, 0, -1, 0};
    int dc[4] = {0, 1, 0, -1};
    for(int i=0; i<4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(!is_range(nr, nc)) continue;
        if(vst[nr][nc]) continue;
        if(a[nr][nc] != a[r][c]) continue;
        ret += dfs(nr, nc);
    }
    return ret;
}
void dfs_color(int r, int c) {
    color[r][c] = true;
    int dr[4] = {1, 0, -1, 0};
    int dc[4] = {0, 1, 0, -1};
    for(int i=0; i<4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(!is_range(nr, nc)) continue;
        if(color[nr][nc]) continue;
        if(a[nr][nc] != a[r][c]) continue;
        dfs_color(nr, nc);
    }
}
int get_tressure() {
    memset(vst, false, sizeof(vst));
    
    int ret = 0;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            if(vst[i][j]) continue;
            int tressure = dfs(i, j);
            if(tressure >= 3) {
                ret += tressure;
            }
        }
    }
    return ret;
}
void print_a() {
    printf("==== aaaaa ====\n");
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}
bool finished = false;
pair<int, pii> find_candidate() {
    int max_score = -1;
    for(int i=2; i<=4; i++) {
        for(int j=2; j<=4; j++) {
            for(int k=0; k<4; k++) {
                rotate_90(i, j);
                int score = get_tressure();
                max_score = max(max_score, score);
            }
        }
    }
    
    if(max_score == 0) {
        finished = true;
        return make_pair(-1, pii(-1,-1));
    }
    vector<pair<int, pii> > cands;
    for(int i=2; i<=4; i++) {
        for(int j=2; j<=4; j++) {
            for(int k=0; k<4; k++) {
                rotate_90(i, j);
                int score = get_tressure();
                if(max_score == score) {
                    cands.push_back(make_pair(k, pii(i, j)));
                }
            }
        }
    }
    sort(cands.begin(), cands.end(), compare);
    
    return cands[0];
}
int get_real_tressure() {
    memset(vst, false, sizeof(vst));
    memset(color, false, sizeof(color));
    
    int ret = 0;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            if(vst[i][j]) continue;
            int tressure = dfs(i, j);
            if(tressure >= 3) {
                ret += tressure;
                dfs_color(i, j);
            }
        }
    }
    return ret; 
}
int idx = 1;
void add_tressure() {
    for(int j=1; j<=n; j++) {
        for(int i=n; i>=1; i--) {
            if(!color[i][j]) continue;
            a[i][j] = t[idx++];
        }
    }
}
void go() {
    pair<int, pii> cand = find_candidate();
    // printf("k: %d\n", k);
    if(finished) return;
    
    int r, c; tie(r, c) = cand.ss;
    for(int i=0; i<=cand.ff; i++) {
        rotate_90(r, c);
    }
    int ans = 0;
    while(true) {
        int score = get_real_tressure();
        ans += score;
        // printf("score: %d\n", score);
        if(score == 0) break;
        add_tressure();
        // print_a();
    }
    printf("%d ", ans);
}
int main(void) {
    n = 5;
    cin >> k >> m;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            cin >> a[i][j];
        }
    }
    for(int i=1; i<=m; i++) {
        cin >> t[i];
    }
    while(k-- && !finished) {
        go();   
    }
}