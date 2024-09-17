/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <bits/stdc++.h>
#define endl '\n'
#define INF 987654321
using namespace std;
using pii = pair<int,int>;

const int MAX = 10+7;

int N, M, K;
int a[MAX][MAX];
int attack_turn[MAX][MAX];
int turn;
pii find_attacker() {
    int min_attack = 987654321;
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            if(a[i][j] <= 0) continue;
            min_attack = min(min_attack, a[i][j]);
        }
    }
    
    vector<pii> min_attacks;
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            if(a[i][j] <= 0) continue;
            if(min_attack == a[i][j]) {
               min_attacks.push_back(pii(i,j)); 
            }
        }
    }
    
    int max_turn = -1;
    for(auto cand : min_attacks) {
        auto [r, c] = cand;
        max_turn = max(max_turn, attack_turn[r][c]);
    }
    vector<pii> max_turns;
    for(auto cand : min_attacks) {
        auto [r, c] = cand;
        if(max_turn == attack_turn[r][c]) {
            max_turns.push_back(pii(r,c));
        }
    }
    
    int max_sum = -1;
    for(auto cand : max_turns) {
        auto [r, c] = cand;
        max_sum = max(max_sum, r + c);
    }
    vector<pii> max_sums;
    for(auto cand : max_turns) {
        auto [r, c] = cand;
        if(max_sum == (r+c)) {
            max_sums.push_back(pii(r,c)); 
        }
    }
    
    int max_c = -1;
    for(auto cand : max_sums) {
        auto [r, c] = cand;
        max_c = max(max_c, c);
    }
    for(auto cand : max_sums) {
        auto [r, c] = cand;
        if(max_c == c) {
            return pii(r, c);
        }
    }
    
    return pii(-1, -1);
}
pii find_defender(pii attacker) {
    int max_attack = -1;
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            if(a[i][j] <= 0) continue;
            if(i == attacker.first && j == attacker.second) continue;
            max_attack = max(max_attack, a[i][j]);
        }
    }
    vector<pii> max_attacks;
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            if(a[i][j] <= 0) continue;
            if(i == attacker.first && j == attacker.second) continue;
            if(max_attack == a[i][j]) {
               max_attacks.push_back(pii(i,j)); 
            }
        }
    }
    
    int min_turn = INF;
    for(auto cand : max_attacks) {
        auto [r, c] = cand;
        min_turn = min(min_turn, attack_turn[r][c]);
    }
    vector<pii> min_turns;
    for(auto cand : max_attacks) {
        auto [r, c] = cand;
        if(min_turn == attack_turn[r][c]) {
            min_turns.push_back(pii(r,c));
        }
    }
    
    int min_sum = INF;
    for(auto cand : min_turns) {
        auto [r, c] = cand;
        min_sum = min(min_sum, r + c);
    }
    vector<pii> min_sums;
    for(auto cand : min_turns) {
        auto [r, c] = cand;
        if(min_sum == (r+c)) {
            min_sums.push_back(pii(r,c)); 
        }
    }
    
    int min_c = INF;
    for(auto cand : min_sums) {
        auto [r, c] = cand;
        min_c = min(min_c, c);
    }
    for(auto cand : min_sums) {
        auto [r, c] = cand;
        if(min_c == c) {
            return pii(r, c);
        }
    }
    
    return pii(-1, -1);
}
void apply_handicap(pii attacker) {
    auto [r, c] = attacker;
    
    attack_turn[r][c] = turn;
    a[r][c] += (N + M);
}
int dr[4] = {0, 1, 0, -1};
int dc[4] = {1, 0, -1, 0};
pii move(int r, int c) {
    if(r > N) r = 1;
    if(r < 1) r = N;
    if(c > M) c = 1;
    if(c < 1) c = M;
    
    return pii(r, c);
}
int back_r[MAX][MAX];
int back_c[MAX][MAX];
bool can_raser(pii attacker, pii defender) {
    bool vst[MAX][MAX];
    memset(vst, false, sizeof vst);
    
    queue<pii> q;
    q.push(attacker);
    while(q.size()) {
        auto [r, c] = q.front();
        q.pop();
        
        if(r == defender.first && c == defender.second) {
            return true;
        }
        
        for(int i=0; i<4; i++) {
           auto [nr, nc] = move(r + dr[i], c + dc[i]); 
           if(a[nr][nc] <= 0) continue;
           if(vst[nr][nc]) continue;
           
           vst[nr][nc] = true;
           back_r[nr][nc] = r;
           back_c[nr][nc] = c;
           q.push(pii(nr, nc));
        }
    }
    
    return false;
}
bool is_affect[MAX][MAX];
void go_raser(pii attacker, pii defender) {
    memset(is_affect, false, sizeof is_affect);
    
    int damage = a[attacker.first][attacker.second]; 
    is_affect[attacker.first][attacker.second] = true;
    
    auto [r, c] = defender;
    a[r][c] -= damage;
    is_affect[r][c] = true;
    
    int nr = back_r[r][c];
    int nc = back_c[r][c];
    while(!(nr == attacker.first && nc == attacker.second)) {
        a[nr][nc] -= (damage/2);
        is_affect[nr][nc] = true; 
        
        int nnr = back_r[nr][nc];
        int nnc = back_c[nr][nc];
        
        nr = nnr;
        nc = nnc;
    }
}
void potan(pii attacker, pii defender) {
    memset(is_affect, false, sizeof is_affect);
    
    int damage = a[attacker.first][attacker.second]; 
    is_affect[attacker.first][attacker.second] = true;
    
    auto [r, c] = defender;
    a[r][c] -= damage;
    is_affect[r][c] = true;
    
    int dr[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int dc[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
    for(int i=0; i<8; i++) {
       auto [nr, nc] = move(r + dr[i], c + dc[i]); 
       is_affect[nr][nc] = true;
       if(nr == attacker.first && nc == attacker.second) {
           continue;
       }
       if(nr == defender.first && nc == defender.second) {
           continue;
       }
       if(a[nr][nc] <= 0) continue;
       
       a[nr][nc] -= (damage/2);
    }
}
void jungbi() {
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            if(a[i][j] <= 0) continue;
            if(is_affect[i][j]) continue;
            a[i][j]++;
        }
    }
}
void do_turn() {
   pii attacker = find_attacker();     
   pii defender = find_defender(attacker);
   
   apply_handicap(attacker);
   
    if(can_raser(attacker, defender)) {
       go_raser(attacker, defender); 
    } else {
       potan(attacker, defender); 
    }
    
    jungbi();
}
int main()
{
    cin >> N >> M >> K;
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            cin >> a[i][j];
        }
    }
    
    while(K--) {
        turn++;
        do_turn();
    }
    
    int ans = -1;
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            ans = max(ans, a[i][j]);
        }
    }

    cout << ans << endl;
    return 0;
}