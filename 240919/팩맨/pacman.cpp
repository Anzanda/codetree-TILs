/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <bits/stdc++.h>
#define endl '\n'
#define ff first
#define ss second
using namespace std;
using pii = pair<int,int>;

const int MAXM = 1e6+7;


int m, t;
pii packman;
int monster_cnt[5][5];
int dead_turn[5][5];
bool is_dead[MAXM];
vector<pii> monster;
vector<int> dir;
queue<pair<pii, int>> eggs;
int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[8] = {0, -1, -1, -1, 0, 1, 1, 1};
void replicate() {
    if(monster.size() != dir.size()) {
        exit(-1);
    }
    // 1~n까지 테스트 하는지 테스트
    for(int i=1; i<monster.size(); i++) {
        if(is_dead[i]) continue;
        auto [r, c] = monster[i];
        int d = dir[i];
        
        eggs.push(make_pair(pii(r, c), d));
    }
}
bool is_range(int r, int c) {
    return r>=1 && r<=4 && c>=1 && c<=4;
}
bool move_45(int curr) {
    auto [r, c] = monster[curr];
    int d = dir[curr];
    
    int nr = r + dr[d];
    int nc = c + dc[d];
    if(!is_range(nr, nc)) {
        return false;    
    }
    // 시체가 있는 경우
    if(dead_turn[nr][nc] > 0) {
        return false;
    }
    if(nr == packman.ff && nc == packman.ss) {
        return false;
    }
    
    monster[curr] = pii(nr, nc);
    monster_cnt[nr][nc]++;
    monster_cnt[r][c]--;
    
    return true;
}
void move_monster(int curr) {
    // 8방향을 다 돌았는데도 불구하고 움직일 수 없다면...
    for(int i=0; i<8; i++) {
        if(move_45(curr)) {
            break;
        } else {
            dir[curr] = (dir[curr] + 8 + 1) % 8;
        }
    } 
}
void move_monsters() {
    for(int i=1; i<monster.size(); i++) {
        if(is_dead[i]) continue;
        move_monster(i); 
    }
}
void dead(int r, int c) {
    for(int i=1; i<monster.size(); i++) {
        if(is_dead[i]) continue;
        if(r == monster[i].ff && c == monster[i].ss) {
            is_dead[i] = true;
        }
    }
    dead_turn[r][c] = 4;
    monster_cnt[r][c] = 0;
}
void move_packman() {
    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = {0, -1, 0, 1};
    auto [r, c] = packman;
    int max_eat = -1;
    for(int i=0; i<4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(!is_range(nr, nc)) continue;
        
        int eat1 = monster_cnt[nr][nc];
        monster_cnt[nr][nc] = 0;
        for(int j=0; j<4; j++) {
            int nnr = nr + dr[j];
            int nnc = nc + dc[j];
            if(!is_range(nnr, nnc)) continue;
            
            int eat2 = monster_cnt[nnr][nnc] + eat1; 
            monster_cnt[nnr][nnc] = 0;
            for(int k=0; k<4; k++) {
                int nnnr = nnr + dr[k];
                int nnnc = nnc + dc[k];
                if(!is_range(nnnr, nnnc)) continue;
                
                int eat3 = monster_cnt[nnnr][nnnc] + eat2;
                monster_cnt[nnnr][nnnc] = 0;
                max_eat = max(max_eat, eat3);
                monster_cnt[nnnr][nnnc] += (eat3 - eat2);
            }
            monster_cnt[nnr][nnc] += (eat2 - eat1);
        }
        monster_cnt[nr][nc] += eat1;
    }
    // 다 끝났는데 max_eat가 -1이라면? 그럴리는 없다. 0임.
    
    for(int i=0; i<4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(!is_range(nr, nc)) continue;
        
        int eat1 = monster_cnt[nr][nc];
        monster_cnt[nr][nc] = 0;
        for(int j=0; j<4; j++) {
            int nnr = nr + dr[j];
            int nnc = nc + dc[j];
            if(!is_range(nnr, nnc)) continue;
            
            int eat2 = monster_cnt[nnr][nnc] + eat1; 
            monster_cnt[nnr][nnc] = 0;
            for(int k=0; k<4; k++) {
                int nnnr = nnr + dr[k];
                int nnnc = nnc + dc[k];
                if(!is_range(nnnr, nnnc)) continue;
                
                int eat3 = monster_cnt[nnnr][nnnc] + eat2;
                monster_cnt[nnnr][nnnc] = 0;
                if(max_eat == eat3) {
                    dead(nr, nc);
                    dead(nnr, nnc);
                    dead(nnnr, nnnc);
                    // printf("packman moving====\n");
                    // printf("(%d, %d)\n", r, c);
                    // printf("(%d, %d)\n", nr, nc);
                    // printf("(%d, %d)\n", nnr, nnc);
                    // printf("(%d, %d)\n", nnnr, nnnc);
                    
                    packman = pii(nnnr, nnnc);
                    return;
                }
                monster_cnt[nnnr][nnnc] += (eat3 - eat2);
            }
            monster_cnt[nnr][nnc] += (eat2-eat1);
        }
        monster_cnt[nr][nc] += eat1;
    }
}
void manage_deads() {
    for(int i=1; i<=4; i++) {
        for(int j=1; j<=4; j++) {
            if(dead_turn[i][j] == 0) continue;
            
            //실제로 2턴동안 남아있는게 맞는지 테스트
            dead_turn[i][j]--;
        }
    }
}
void hatch() {
    while(eggs.size()) {
        pair<pii, int> egg = eggs.front();
        eggs.pop();
        
        auto [r, c] = egg.ff;
        int d = egg.ss;
        
        monster_cnt[r][c]++;
        monster.push_back(pii(r,c));
        dir.push_back(d);
    }
    
    if(monster.size() != dir.size()) {
        exit(-1);
    }
}
void go_turn() {
    replicate();
    move_monsters();
    move_packman();
    manage_deads();
    hatch();
    // for(int i=1; i<monster.size(); i++) {
    //     if(is_dead[i]) {
    //         printf("monster%d is dead\n", i);
    //     }
    //     auto [r, c] = monster[i];
    //     int d = dir[i];
        
    //     printf("montser%d: (%d, %d) | %d\n", i, r, c, d);
    // }
    // for(int i=1; i<monster.size(); i++) {
    //     if(is_dead[i]) dead++;
    //     else live++;
    // }
    // printf("monster.size(): %d\n", monster.size());
    // printf("dead: %d, live: %d\n", dead, live);
}
int main()
{
    cin >> m >> t;
    cin >> packman.ff >> packman.ss;
    
    monster.push_back(pii(-1,-1)); // 1-index
    dir.push_back(-1);
    for(int i=1; i<=m; i++) {
        int r, c, d;
        cin >> r >> c >> d;
        d--;
        monster.push_back(pii(r,c));
        monster_cnt[r][c]++;
        dir.push_back(d);
    }

    while(t--) {
        go_turn();
    }
    int ans = 0;
    for(int i=1; i<monster.size(); i++) {
        if(is_dead[i]) continue;
        ans++;
    }
    cout << ans << endl;
    return 0;
}