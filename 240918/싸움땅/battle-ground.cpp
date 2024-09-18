#include <bits/stdc++.h>
#define endl '\n'
#define int long long
#define ff first
#define ss second
#define INF 987654321
using namespace std;
using pii = pair<int,int>;

const int MAXN = 20+7;
const int MAXM = 30+7;

int n,m,k;
vector<int> gun[MAXN][MAXN];
pii loc[MAXM];
int player_gun[MAXM];
int base[MAXM];
int dir[MAXM];
int point[MAXM];

// 상 우 하 좌
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};
bool is_range(int r, int c) {
    return r>=1 && r<=n && c>=1 && c<=n;
}
void move_180(int curr) {
    auto [r, c] = loc[curr];
    
    int nr = r + dr[dir[curr]];
    int nc = c + dc[dir[curr]];
    
    if(!is_range(nr, nc)) {
        dir[curr] = (dir[curr] + 4 + 2)%4;
        nr = r + dr[dir[curr]];
        nc = c + dc[dir[curr]];
    }
    
    loc[curr] = pii(nr, nc);
}
void move_90(int curr) {
    auto [r, c] = loc[curr];
    
    int nr = r + dr[dir[curr]];
    int nc = c + dc[dir[curr]];
    if(!is_range(nr, nc)) {
        dir[curr] = (dir[curr] + 4 + 1)%4;
        move_90(curr);
        return;
    }
    for(int i=1; i<=m; i++) {
        if(m == curr) continue;
        if(nr == loc[i].ff && nc == loc[i].ss) {
            dir[curr] = (dir[curr] + 4 + 1)%4;
            move_90(curr);
            return;
        }
    }
    
    loc[curr] = pii(nr, nc);
}
void get_a_gun(int curr) {
    auto [r, c] = loc[curr];
    if(gun[r][c].size() == 0) {
        return;
    }
    
    sort(gun[r][c].begin(), gun[r][c].end());
    
    if(gun[r][c].back() <= player_gun[curr]) {
        return;
    }
    if(player_gun[curr] != 0) {
        //그저 총을 바꾸면 됨.
        int tmp = player_gun[curr];
        player_gun[curr] = gun[r][c].back();
        gun[r][c][gun[r][c].size()-1] = tmp;
    } else {
        player_gun[curr] = gun[r][c].back();
        
        // 여기 테스트 해야댐...
        vector<int> new_gun;
        for(int i=0; i<gun[r][c].size()-1; i++) {
           new_gun.push_back(gun[r][c][i]); 
        }
        gun[r][c] = new_gun;
    }
    
}
void lose(int curr) {
    auto [r, c] = loc[curr];
    if(player_gun[curr] != 0) {
        gun[r][c].push_back(player_gun[curr]);
        player_gun[curr] = 0;
    }
    
    move_90(curr);
    
    get_a_gun(curr);
}
void winner(int curr) {
    get_a_gun(curr);
}
bool fight(int curr) {
    int to_fight = -1;
    auto [r, c] = loc[curr];
    for(int i=1; i<=m; i++) {
       if(i == curr) continue;
       if(loc[i].ff == r && loc[i].ss == c) {
           to_fight = i;
           break;
       }
    }
    if(to_fight == -1) return false;
    
    int curr_attack = base[curr] + player_gun[curr];
    int to_fight_attack = base[to_fight] + player_gun[to_fight];
    
    int diff = abs(curr_attack - to_fight_attack);
    
    if(curr_attack > to_fight_attack) {
        point[curr] += diff;
        lose(to_fight);
        winner(curr);
        
    } else if(curr_attack < to_fight_attack) {
        point[to_fight] += diff;
        lose(curr);
        winner(to_fight);
    } else {
        if(base[curr] > base[to_fight]) {
            point[curr] += diff;
            lose(to_fight);
            winner(curr);
            
        }  else {
            point[to_fight] += diff;
            lose(curr);
            winner(to_fight);
        }
    }
    
    return true;
}
void go_round() {
    for(int i=1; i<=m; i++) {
       move_180(i);
       if(!fight(i)) {
           get_a_gun(i);
       }
    }
}
signed main(void) {
   cin >> n >> m >> k; 
   for(int i=1; i<=n; i++) {
       for(int j=1; j<=n; j++) {
           int tmp;
           cin >> tmp;
           if(tmp == 0) continue;
           gun[i][j].push_back(tmp);
       }
   }
   for(int i=1; i<=m; i++) {
       cin >> loc[i].ff >> loc[i].ss;
       cin >> dir[i];
       cin >> base[i];
   }
   
   while(k--) {
       go_round();
    //   cout << "******" << endl;
    //   for(int i=1; i<=n; i++) {
    //       for(int j=1; j<=n; j++) {
    //           cout << gun[i][j].size() << ' ';
    //       }
    //       cout << endl;
    //   }
    //   cout << "******" << endl;
    //   for(int i=1; i<=m; i++) {
    //         printf("player%d: (%d, %d) | %d\n", i, loc[i].ff, loc[i].ss, player_gun[i]) ;
    //   }
    //   printf("=========\n");
   }
   
   for(int i=1; i<=m; i++) {
       cout << point[i] << ' ';
   }
   cout << endl;
}