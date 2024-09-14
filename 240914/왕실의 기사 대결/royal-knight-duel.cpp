/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
using pii = pair<int,int>;

const int MAXL = 40+7;
const int MAXN = 30+7;

int L, N, Q;
int chess[MAXL][MAXL];
pii loc[MAXN];
int h[MAXN];
int w[MAXN];
int k[MAXN];
int ans;

int to_move;
int direction; // 위쪽, 오른쪽, 아래쪽, 왼쪽
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};
bool is_range(int r, int c) {
    return r>=1 && r<=L && c>=1 && c<=L;
}
bool can_move(pii loc[], int to_move, int direction) {
    auto [r, c] = loc[to_move];
    
    int nr = r + dr[direction];
    int nc = c + dc[direction];
    
    for(int i=nr; i<=nr+h[to_move]; i++) {
        for(int j=nc; j<=nc+w[to_move]; j++) {
            if(!is_range(i, j)) {
                return false;
            }
            if(chess[i][j] == 2) {
                return false;
            }
        }
    }
    
    return true;
}
void move(pii loc[], int to_move, int direction) {
    auto [r, c] = loc[to_move];
    
    int nr = r + dr[direction];
    int nc = c + dc[direction];
    
    loc[to_move] = pii(nr, nc);
}
void find_victims(pii loc[], int moved, queue<int> &victims) {
    vector<int> ret;
    
    auto [r1, c1] = loc[moved];
    for(int i=1; i<=N; i++) {
        if(i == moved) continue;
        if(k[i] <= 0) continue;
        
        auto [r2, c2] = loc[i]; 
        if(r1 + h[moved] < r2) continue;
        if(c1 + w[moved] < c2) continue;
        if(r2 + h[i] < r1) continue;
        if(c2 + w[i] < c1) continue;
        
        victims.push(i);
    }
}
bool can_query(int to_move, int direction) {
    if(k[to_move] <= 0) return false;
    
    pii tmp_loc[MAXN];
    memcpy(tmp_loc, loc, sizeof tmp_loc);
    
    if(!can_move(tmp_loc, to_move, direction)) {
        return false;
    }
    move(tmp_loc, to_move, direction);
    
    queue<int> victims;
    find_victims(tmp_loc, to_move, victims);
    while(victims.size()) {
        int victim = victims.front();
        victims.pop();
        
        if(!can_move(tmp_loc, victim, direction)) {
            return false;
        }
        move(tmp_loc, victim, direction);
        
        find_victims(tmp_loc, victim, victims);
    }
    
    return true;
}
void update_damage(pii loc[], int moved) {
    auto [r, c] = loc[moved];
    
    int damaged =0;
    for(int i=r; i<=r+h[moved]; i++) {
        for(int j=c; j<=c+w[moved]; j++) {
            if(chess[i][j] == 1) {
                damaged++;
            }
        }
    }
    
    k[moved] -= damaged;
}
void query() {
    cin >> to_move >> direction;
    
    if(!can_query(to_move, direction)) {
        return;
    }
    
    move(loc, to_move, direction);
    
    queue<int> victims;
    find_victims(loc, to_move, victims);
    while(victims.size()) {
        int victim = victims.front();
        victims.pop();
        
        
        move(loc, victim, direction);
        update_damage(loc, victim);
        
        find_victims(loc, victim, victims);
    }
    
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    
    cin >> L >> N >> Q;
    for(int i=1; i<=L; i++) {
        for(int j=1; j<=L; j++) {
            cin >> chess[i][j];
        }
    }
    
    for(int i=1; i<=N; i++) {
        cin >> loc[i].first >> loc[i].second;
        cin >> h[i];
        cin >> w[i];
        cin >> k[i];
        h[i]--;
        w[i]--;
    }
    
    int origin_k[MAXN];
    memcpy(origin_k, k, sizeof origin_k);
    
    for(int i=1; i<=Q; i++) {
        query();
    }
    
    for(int i=1; i<=N; i++) {
        if(k[i] <= 0) continue;
        ans += (origin_k[i] - k[i]);
    }
    
    cout << ans << endl;

    return 0;
}