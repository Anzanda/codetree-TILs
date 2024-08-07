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

const int INF = 987654321;
const int MAXN = 50+7;
const int MAX = 30+7;

int n, t, p, power_of_rudolf, power_of_santa;
pii loc_rudolf;
int dir_rudolf;
pii loc_santa[MAX];
int dir_santa[MAX];
bool is_alive[MAX];
int paralyzed[MAX];
int score[MAX];
bool vst[MAXN][MAXN];
bool is_range(int r, int c) {
    return r>=1 && r<=n && c>=1 && c<=n;
}
void update_status() {
    for(int i=1; i<=p; i++) {
        auto [r, c] = loc_santa[i];
        if(!is_range(r, c)) {
            is_alive[i] = false;
        }
    }
}
bool is_finished() {
    for(int i=1; i<=p; i++) {
        if(is_alive[i]) {
            return false;
        }
    }
    return true;
}
int get_closest_santa() {
    int min_dist = INF;
    for(int i=1; i<=p; i++) {
        if(!is_alive[i]) continue;
        auto [x1, y1] = loc_rudolf;
        auto [x2, y2] = loc_santa[i];
        int dist = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
        min_dist = min(min_dist, dist);
    }
    if(min_dist == INF) {
        cout << "error" << endl;
        return -1;
    }
    
    int cand_santa = -1;
    int min_x = -1;
    int min_y = -1;
    for(int i=1; i<=p; i++) {
        if(!is_alive[i]) continue;
        auto [x1, y1] = loc_rudolf;
        auto [x2, y2] = loc_santa[i];
        int dist = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
        if(min_dist == dist) {
            if(x2 > min_x) {
                min_x = x2;
                min_y = y2;
                cand_santa = i;
            } else if(x2 == min_x) {
                if(y2 > min_y) {
                    min_x = x2;
                    min_y = y2;
                    cand_santa = i;
                }
            }
        }
    }
    return cand_santa;
}
void interaction(int curr, int dr, int dc) {
    auto [r, c] = loc_santa[curr];
    
    int cand = -1;
    for(int i=1; i<=p; i++) {
        if(curr == i) continue; 
        auto [r1, c1] = loc_santa[i];
        if(r == r1 && c == c1) {
            cand = i; 
            break;
        }
    } 
    if(cand == -1) {
        cout << "error" << endl;
        return;
    }
    
    loc_santa[cand].first += dr;
    loc_santa[cand].second += dc;
    auto [nr, nc] = loc_santa[cand];
    if(!is_range(nr, nc)) {
        return;
    }
    
    if(vst[nr][nc]) {
        interaction(cand, dr, dc);
    } else {
        vst[nr][nc] = true;
    }
}
void move_rudolf() {
    int cand_santa = get_closest_santa();
    if(cand_santa == -1) {
        return;
    }
    
    int dr[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int dc[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
    
    int min_dist = INF;
    for(int i=0; i<8; i++) {
        auto [r, c] = loc_rudolf;
        auto [rr, cc] = loc_santa[cand_santa];
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(!is_range(nr, nc)) continue;
        
        int dist = (nr - rr)*(nr - rr) + (nc - cc)*(nc-cc);
        min_dist = min(min_dist, dist);
    }
    
    for(int i=0; i<8; i++) {
        auto [r, c] = loc_rudolf;
        auto [rr, cc] = loc_santa[cand_santa];
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(!is_range(nr, nc)) continue;
        
        int dist = (nr - rr)*(nr - rr) + (nc - cc)*(nc-cc);
        if(min_dist == dist) {
            loc_rudolf.first = nr;
            loc_rudolf.second = nc;
            dir_rudolf = i;
            break;
        }
    }
}
void crash_rudolf() {
    int cand_santa = -1;
    for(int i=1; i<=p; i++) {
        if(!is_alive[i]) continue;
        auto [x1, y1] = loc_rudolf;
        auto [x2, y2] = loc_santa[i];
        if((x1 == x2) && (y1 == y2)) {
            cand_santa = i; 
        }
    }
    if(cand_santa == -1) {
        return;
    }
    
    score[cand_santa] += power_of_rudolf;
    
    int dr[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int dc[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
    
    auto [r, c] = loc_santa[cand_santa];
    loc_santa[cand_santa].first += (power_of_rudolf * dr[dir_rudolf]);
    loc_santa[cand_santa].second += (power_of_rudolf * dc[dir_rudolf]);
    vst[r][c] = false;
    paralyzed[cand_santa] += 2;
    
    auto [nr, nc] = loc_santa[cand_santa];
    if(!is_range(nr, nc)) return;
    if(vst[nr][nc]) {
        interaction(cand_santa, dr[dir_rudolf], dc[dir_rudolf]);
    } else {
        vst[nr][nc] = true; 
    }
}
void move_santa(int curr) {
    if(!is_alive[curr]) {
        return;
    }
    if(paralyzed[curr]) {
        paralyzed[curr]--;
        return;
    }
    
    // 이때 가장 가까워질 수 있는 방향이 여러 개라면, 상우하좌 우선순위에 맞춰 움직입니다.
    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = {0, 1, 0, -1};
    
    auto [r, c] = loc_santa[curr];
    auto [rr, cc] = loc_rudolf;
    int min_dist = (rr-r)*(rr-r)+(cc-c)*(cc-c);
    for(int i=0; i<4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(!is_range(nr, nc)) continue;
        if(vst[nr][nc]) continue;
        
        auto [rr, cc] = loc_rudolf;
        int dist = (nr-rr)*(nr-rr) + (nc-cc)*(nc-cc);
        min_dist = min(min_dist, dist);
    }
    
    for(int i=0; i<4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(!is_range(nr, nc)) continue;
        if(vst[nr][nc]) continue;
        
        auto [rr, cc] = loc_rudolf;
        int dist = (nr-rr)*(nr-rr) + (nc-cc)*(nc-cc);
        if(dist == min_dist) {
            loc_santa[curr].first = nr;
            loc_santa[curr].second = nc;
            dir_santa[curr] = i;
            break;
        }
    }
    
    auto [nr, nc] = loc_santa[curr];
    if(!is_range(nr, nc)) return;
    // 산타가 움직인 경우임으로(충돌x) 상호작용은 고려하지 않아도 된다.
    vst[r][c] = false;
    vst[nr][nc] = true;
}
void crash_santa(int curr) {
    auto [r, c] = loc_santa[curr];
    auto [rr, cc] = loc_rudolf;
    if(r != rr || c != cc) return;
    
    // 이때 가장 가까워질 수 있는 방향이 여러 개라면, 상우하좌 우선순위에 맞춰 움직입니다.
    score[curr] += power_of_santa;
    
    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = {0, 1, 0, -1};
    
    int dir = (dir_santa[curr]+2)%4;
    loc_santa[curr].first += (power_of_santa*dr[dir]);
    loc_santa[curr].second += (power_of_santa*dc[dir]);
    vst[r][c] = false; // 옛날 자리
    paralyzed[curr] += 1;
    
    auto [nr, nc] = loc_santa[curr];
    if(!is_range(nr, nc)) {
        return;
    }
    if(vst[nr][nc]) {
        interaction(curr, dr[dir], dc[dir]); 
    } else {
        vst[nr][nc] = true;
    }
}
void move_santas() {
    for(int i=1; i<=p; i++) {
        move_santa(i);
        update_status();
        crash_santa(i); 
        update_status();
    }
}
void turn() {
    move_rudolf();
    crash_rudolf();
    update_status();
    
    move_santas();
    
    for(int i=1; i<=p; i++){
        if(!is_alive[i]) continue;
        score[i] += 1;
    }
    if(is_finished()) {
        t = 0;
    }
}
int main()
{
    cin >> n >> t >> p >> power_of_rudolf >> power_of_santa;
    cin >> loc_rudolf.first >> loc_rudolf.second; 
    for(int i=1; i<=p; i++) {
        int curr;
        cin >> curr;
        cin >> loc_santa[curr].first >> loc_santa[curr].second;
        is_alive[curr] = true;
    }
    while(t--) {
        turn();
    }
    
    for(int i=1; i<=p; i++) {
        cout << score[i] << ' ';
    }
    cout << endl;
    
    return 0;
}