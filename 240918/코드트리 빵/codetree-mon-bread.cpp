/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <bits/stdc++.h>
#define INF 987654321
#define ff first
#define ss second
#define endl '\n'
using namespace std;
using pii = pair<int,int>;

const int MAXN = 15+7;
const int MAXM = 30+7;

int t;
int n, m;
int a[MAXN][MAXN];
pii goal[MAXM];
pii loc[MAXM];
bool all_finished;
bool finished[MAXM];
bool can_move[MAXN][MAXN];
int dist[MAXN][MAXN];
pii back[MAXN][MAXN];
int dr[4] = {-1, 0, 0, 1};
int dc[4] = {0, -1, 1, 0};
bool is_range(int r, int c) {
    return r>=1 && r <= n && c>=1 && c<=n;
}
void bfs(pii st, pii en) {
    memset(dist, -1, sizeof dist);
    
    queue<pii> q;
    q.push(st);
    dist[st.ff][st.ss] = 0;
    
    while(q.size()) {
        auto [r, c] = q.front();
        q.pop();
        
        if(r == en.first && c == en.second) {
           break; 
        }
        
        for(int i=0; i<4; i++) {
            int nr = r +dr[i];
            int nc = c + dc[i];
            if(!is_range(nr, nc)) continue;
            if(dist[nr][nc] != -1) continue;
            if(!can_move[nr][nc]) continue;
            
            dist[nr][nc] = dist[r][c] + 1;
            back[nr][nc] = pii(r, c);
            q.push(pii(nr, nc));
        }
    }
}
void move(int curr) {
    if(finished[curr]) return;
    if(loc[curr].ff == 0 && loc[curr].ss == 0) {
        // 아직 베이스캠프 못옴..ㅜ
        return;
    }
    
    bfs(loc[curr], goal[curr]);
      
    auto [r, c] = goal[curr];
    auto [nr, nc] = back[r][c];
    while(!(nr == loc[curr].ff && nc == loc[curr].ss)) {
       auto [nnr, nnc] = back[nr][nc];
       
       r = nr;
       c = nc;
       
       nr = nnr;
       nc = nnc;
    }
    
    loc[curr] = pii(r,c);
}
void arrive(int curr) {
    auto [r1, c1] = loc[curr];
    auto [r2, c2] = goal[curr];
    if(r1 == r2 && c1 == c2) {
        can_move[r2][c2] = false;
        finished[curr] = true;
    }
}
bool is_all_finished() {
    for(int i=1; i<=m; i++) {
        if(!finished[i]) return false;
    }
    return true;
}
void go_basecamp(int curr) {
    if(curr > m) return;
    if(finished[curr]) return;
    
    int min_dist = INF;
    auto [r, c] = goal[curr];
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            if(a[i][j] != 1) continue;
            if(!can_move[i][j]) continue;
            bfs(pii(i, j), pii(r, c));
            min_dist = min(min_dist, dist[r][c]);
        }
    }
    vector<pii> cand;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            if(a[i][j] != 1) continue;
            if(!can_move[i][j]) continue;
            bfs(pii(i, j), pii(r, c));
            if(min_dist == dist[r][c]) {
                cand.push_back(pii(i,j));
            }
        }
    }
    sort(cand.begin(), cand.end(), [](const pii &a, const pii &b) {
        if(a.ff == b.ff) return a.ss < b.ss;
        return a.ff < b.ff;
    });
    
    loc[curr] = cand.front();
    can_move[loc[curr].ff][loc[curr].ss] = false;
}
void go_time() {
    for(int i=1; i<=m; i++) {
        move(i); 
    }
    for(int i=1; i<=m; i++) {
        arrive(i);
    }
    if(is_all_finished()) {
        all_finished = true;
        return;
    }
    go_basecamp(t); 
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    
    cin >> n >> m;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            cin >> a[i][j];
        }
    }
    for(int i=1; i<=m; i++) {
        cin >> goal[i].ff >> goal[i].ss; 
    }
    
    memset(can_move, true, sizeof can_move);
    
    while(!all_finished) {
        t++;
        go_time();
    }
    
    cout << t << endl;
    return 0;
}