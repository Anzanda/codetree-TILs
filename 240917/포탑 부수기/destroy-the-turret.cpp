/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <bits/stdc++.h>
#define endl '\n'
#define INF 987654321
using namespace std;
using pii = pair<int,int>;

const int MAXN = 10+7;

int N, M, K;
int a[MAXN][MAXN];
int attack_turn[MAXN][MAXN];


int turn;
pii find_attacker() {
    int min_attack = 987654321;
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            if(a[i][j] <= 0) continue;
            min_attack = min(min_attack, a[i][j]);
        }
    }
    
    vector<pii> cand; 
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            if(a[i][j] <= 0) continue;
            if(min_attack == a[i][j]) {
                cand.push_back(pii(i, j));
            }
        }
    }
    
    int max_attack_turn = -12;
    for(auto loc : cand) {
        auto [r, c] = loc;
        max_attack_turn = max(max_attack_turn, attack_turn[r][c]);
    }
    vector<pii> cand2;
    for(auto loc : cand) {
        auto [r, c] = loc;
        if(max_attack_turn == attack_turn[r][c]) {
            cand2.push_back(pii(r,c));
        }
    }
    
    int max_sum = -12;
    for(auto loc : cand2) {
        auto [r, c] = loc;
        max_sum = max(max_sum, r+c);
    }
    vector<pii> cand3;
    for(auto loc : cand2) {
        auto [r, c] = loc;
        if(max_sum == (r+c)) {
            cand3.push_back(pii(r, c));
        }
    }
    
    int max_c = -12;
    for(auto loc : cand3) {
        auto [r, c] = loc;
        max_c = max(max_c, c);
    }
    for(auto loc: cand3) {
        auto [r, c] = loc;
        if(max_c == c) {
            return pii(r, c);
        }
    }
    return pii(-1, -1);
}
pii find_defender() {
    int max_attack = -12;
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            if(a[i][j] <= 0) continue;
            max_attack = max(max_attack, a[i][j]);
        }
    }
    
    vector<pii> cand; 
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            if(a[i][j] <= 0) continue;
            if(max_attack == a[i][j]) {
                cand.push_back(pii(i, j));
            }
        }
    }
    
    int min_attack_turn = 987654321;
    for(auto loc : cand) {
        auto [r, c] = loc;
        min_attack_turn = min(min_attack_turn, attack_turn[r][c]);
    }
    vector<pii> cand2;
    for(auto loc : cand) {
        auto [r, c] = loc;
        if(min_attack_turn == attack_turn[r][c]) {
            cand2.push_back(pii(r, c));
        }
    }
    
    int min_sum = 987654321;
    for(auto loc : cand2) {
        auto [r, c] = loc;
        min_sum = min(min_sum, r+c);
    }
    vector<pii> cand3;
    for(auto loc : cand2) {
        auto [r, c] = loc;
        if(min_sum == (r+c)) {
            cand3.push_back(pii(r, c));
        }
    }
    
    int min_c = 98765431;
    for(auto loc : cand3) {
        auto [r, c] = loc;
        min_c = min(min_c, c);
    }
    for(auto loc: cand3) {
        auto [r, c] = loc;
        if(min_c == c) {
            return pii(r, c);
        }
    }
    
    return pii(-1, -1);
}

int dr[4] = {0, 1, 0, -1};
int dc[4] = {1, 0, -1, 0};
pii move(pii curr, int d) {
    auto [r,c] = curr;
    int nr = r + dr[d];
    int nc = c + dc[d];
    
    if(nr > N) nr = 1;
    if(nr < 1) nr = N;
    if(nc > M) nc = 1;
    if(nc < 1) nc = M;
    
    return pii(nr, nc);
}
int dp[MAXN][MAXN];
int dfs(pii curr, pii defender) {
    auto [r, c] = curr;
    
    int &ret = dp[r][c];
    if(ret != -1) {
        return ret;
    }
    
    if(r == defender.first && c == defender.second) {
        return ret = 0;
    }
    
    
    ret = INF;
    for(int i=0; i<4; i++) {
        auto [nr, nc] = move(curr, i);
        if(a[nr][nc] <= 0) continue;
        ret = min(ret, 1+dfs(pii(nr,nc), defender));
    }
    
    return ret;
}
bool can_raser(pii attacker, pii defender) {
    memset(dp, -1, sizeof dp);
    int ret = dfs(attacker, defender);
    
    return (ret != INF);
}
bool vst[MAXN][MAXN];
void do_raser(pii attacker, pii defender) {
    // for(int i=1; i<=N; i++) {
    //     for(int j=1; j<=M; j++) {
    //         cout << dp[i][j] << ' ';
    //     }
    //     cout << endl;
    // } 
    memset(vst, false, sizeof vst);
    
    int damage = a[attacker.first][attacker.second];
    a[attacker.first][attacker.second] += (damage/2);
    
    queue<pii> q;
    q.push(attacker);
    while(q.size()) {
        auto [r, c] = q.front();
        q.pop();
        
        vst[r][c] = true;
        if(r == defender.first && c == defender.second) {
            a[r][c] -= damage;
            break;
        } else {
            a[r][c] -= (damage/2);
        }
        for(int i=0; i<4; i++) {
            auto [nr, nc] = move(pii(r, c), i);
            if(dp[r][c] - 1 == dp[nr][nc]) {
                q.push(pii(nr, nc));
                break;
            }
        }
    }
}
pii move_without_dir(int r, int c) {
    int nr = r;
    int nc = c;
    
    if(nr > N) nr = 1;
    if(nr < 1) nr = N;
    if(nc > M) nc = 1;
    if(nc < 1) nc = M;
    
    return pii(nr, nc);
}
void potan(pii attacker, pii defender) {
    memset(vst, false, sizeof vst);
    
    int dr[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int dc[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
    
    int damage = a[attacker.first][attacker.second];
    vst[attacker.first][attacker.second] = true;
    
    auto [r, c] = defender;
    a[r][c] -= damage;
    vst[r][c] = true;
    
    for(int i=0; i<8; i++) {
        auto [nr, nc] = move_without_dir(r + dr[i], c + dc[i]);
        if(a[nr][nc] <= 0) continue;
        vst[nr][nc] = true;
        if(nr == attacker.first && nc == attacker.second) {
            continue;
        }
        a[nr][nc] -= (damage/2);
    }
}
void jungbi() {
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            if(vst[i][j]) continue;
            if(a[i][j] <= 0) continue;
            a[i][j]++;
        }
    } 
}
bool is_finished() {
    int cnt = 0;
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            if(a[i][j] > 0) {
                cnt++;
            }
        }
    }
    return (cnt == 1);
}
void go_turn() {
    auto [r, c]= find_attacker();   
    pii defender = find_defender();
    
    attack_turn[r][c] = turn;
    a[r][c] += (N+M);
    if(can_raser(pii(r, c), defender)) {
        do_raser(pii(r, c), defender); 
    } else {
        potan(pii(r, c), defender);
    }
    jungbi();
    if(is_finished()) {
        K = 0;
        return;
    }
    // cout << "**********" << endl;
    // for(int i=1; i<=N; i++) {
    //     for(int j=1; j<=M; j++) {
    //         cout << a[i][j] << ' ';
    //     }
    //     cout << endl;
    // }
    // cout << "**********" << endl;
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    
    cin >> N >> M >> K;
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            cin >> a[i][j];
        }
    }
    
    memset(attack_turn, -1, sizeof attack_turn);
    while(K--) {
        go_turn();
        turn++;
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