/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <bits/stdc++.h>
#define endl '\n'
#define ff first
#define ss second
using namespace std;
using pii = pair<int,int>;

const int INF = 987654321;

int n, t, p, power_of_rudolf, power_of_santa;
pii rudolf;
pii santa[37];
int score[37];
int paralyzed[37];
bool is_alive[37];
bool vst[55][55];
bool is_range(int r, int c) {
    return r>=1 && r <= n && c >= 1 && c<=n;
}
bool is_range(pii a) {
    return is_range(a.ff, a.ss);
}
int get_distance(pii a, pii b) {
    auto [x1, y1] = a;
    auto [x2, y2] = b;
    return ((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}
int get_candidate() {
    int min_dist = INF;
    for(int i=1; i<=p; i++) {
        if(!is_alive[i]) continue;
        int dist = get_distance(rudolf, santa[i]); 
        min_dist = min(min_dist, dist);
    }
    int cand = -1;
    int min_r = -1;
    int min_c = -1;
    for(int i=1; i<=p; i++) {
        if(!is_alive[i]) continue;
        if(!is_range(santa[i])) continue;
        int dist = get_distance(rudolf, santa[i]);
        if(dist == min_dist) {
            if(min_r < santa[i].ff) {
                min_r = santa[i].ff;
                min_c = santa[i].ss;
                cand = i;
            } else if(min_r == santa[i].ff) {
                if(min_c < santa[i].ss) {
                    min_r = santa[i].ff;
                    min_c = santa[i].ss;
                    cand = i;
                }
            }
        }
    }
    
    return cand;
}
void interaction(int curr, int dr, int dc) {
    int cand = -1;
    for(int i=1; i<=p; i++) {
        if(!is_alive[i]) continue;
        if(!is_range(santa[i])) continue;
        if(curr == i) continue;
        
        int dist = get_distance(santa[curr], santa[i]);
        if(dist == 0) {
            cand = i;
        }
    } 
    if(cand == -1) {
        cout << "error" << endl;
        return;
    }
    
    santa[cand].ff += dr;
    santa[cand].ss += dc;
    
    auto [nr, nc] = santa[cand];
    if(!is_range(nr, nc)) {
        is_alive[cand] = false;
        return;
    }
    if(vst[nr][nc]) {
        interaction(cand, dr, dc); 
    } else {
        vst[nr][nc] = true; 
    }
    return;
}
void crash_rudolf(int dr, int dc) {
    int cand = -1;
    for(int i=1; i<=p; i++) {
        if(!is_alive[i]) continue;
        if(!is_range(santa[i])) continue;
        
        int dist = get_distance(rudolf, santa[i]);
        if(dist == 0) {
            cand = i;
        }
    } 
    if(cand == -1) return;
    
    score[cand] += (power_of_rudolf); 
    
    vst[santa[cand].ff][santa[cand].ss] = false;
    santa[cand].ff += (power_of_rudolf * dr);
    santa[cand].ss += (power_of_rudolf * dc);
    paralyzed[cand] = 2;
    
    if(!is_range(santa[cand])) {
        is_alive[cand] = false;
        return;
    }
    
    auto [nr, nc] = santa[cand];
    if(vst[nr][nc]) {
        interaction(cand, dr, dc);  
    } else {
        vst[nr][nc] = true;
    }
}
void move_rudolf() {
   int cand = get_candidate();  
   if(cand == -1) {
       return;
   }
   
   int dr[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
   int dc[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
   
   int min_dist = INF;
   for(int i=0; i<8; i++) {
       int nr = rudolf.ff + dr[i];
       int nc = rudolf.ss + dc[i];
       if(!is_range(nr, nc)) continue;
       
        int dist = get_distance(pii(nr, nc), santa[cand]); 
        min_dist = min(min_dist, dist);
   }
   
   int dir = -1;
   for(int i=0; i<8; i++) {
       int nr = rudolf.ff + dr[i];
       int nc = rudolf.ss + dc[i];
       if(!is_range(nr, nc)) continue;
       
        int dist = get_distance(pii(nr, nc), santa[cand]); 
        if(dist == min_dist) {
            rudolf.ff = nr;
            rudolf.ss = nc;
            dir = i;
            break;
        }
   }
   
   crash_rudolf(dr[dir], dc[dir]);
}
void crash_santa(int curr, int dr, int dc) {
    int dist = get_distance(rudolf, santa[curr]);
    if(dist > 0) return;
    
    score[curr] += (power_of_santa);
    
    vst[santa[curr].ff][santa[curr].ss] = false;
    santa[curr].ff += (power_of_santa * dr);
    santa[curr].ss += (power_of_santa * dc);
    paralyzed[curr] = 1;
    
    if(!is_range(santa[curr])) {
        is_alive[curr] = false;
        return;
    }
    auto [nr, nc] = santa[curr];
    if(vst[nr][nc]) {
        interaction(curr, dr, dc);  
    } else {
        vst[nr][nc] = true;
    }
    
}
void move_santa(int curr) {
    if(!is_alive[curr]) return;
    if(paralyzed[curr] > 0) {
        paralyzed[curr] -= 1;   
        return;
    } 
    
    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = {0, 1, 0, -1};
    
    auto [old_r, old_c] = santa[curr];
    int min_dist = get_distance(santa[curr], rudolf);
    for(int i=0; i<4; i++) {
        int nr = santa[curr].ff + dr[i];
        int nc = santa[curr].ss + dc[i];
        if(!is_range(nr, nc)) continue;
        if(vst[nr][nc]) continue;
        
        int dist = get_distance(pii(nr, nc), rudolf);
        min_dist = min(min_dist, dist);
    }
    int dir = -99;
    for(int i=0; i<4; i++) {
        int nr = santa[curr].ff + dr[i];
        int nc = santa[curr].ss + dc[i];
        if(!is_range(nr, nc)) continue;
        if(vst[nr][nc]) continue;
        
        int dist = get_distance(pii(nr, nc), rudolf);
        if(dist == min_dist) {
            dir = i;
            santa[curr].ff = nr;
            santa[curr].ss = nc;
            break;
        }
    }
    
    auto [nr, nc] = santa[curr];
    vst[old_r][old_c] = false;
    vst[nr][nc] = true;
    
    if(dir != -99) {
        int new_dir = (dir+2)%4;
        crash_santa(curr, dr[new_dir], dc[new_dir]);
    }
}
void move_santas() {
    for(int i=1; i<=p; i++) {
        if(!is_alive[i]) continue;
        move_santa(i);
    }
}
void update_score() {
    for(int i=1; i<=p; i++) {
        if(!is_alive[i]) continue;
        score[i]++;
    }
}
bool is_finished() {
    for(int i=1; i<=p; i++) {
        if(is_alive[i]) return false;
    }
    return true;
}
void turn() {
    move_rudolf();
    move_santas();
    update_score();
    // printf("turn: %d\n", t);
    // printf("rudolf: (%d, %d)\n", rudolf.ff, rudolf.ss);
    // for(int i=1; i<=p; i++) {
    //     printf("santa%d: (%d, %d)\n", i, santa[i].ff, santa[i].ss);
    // }
    // printf("score: ");
    // for(int i=1; i<=p; i++) {
    //     printf("%d ", score[i]);
    // }
    // printf("\n\n");
    
    if(is_finished()) {
        t = 0;
    }
}
int main()
{
    cin >> n >> t >> p >> power_of_rudolf >> power_of_santa;
    cin >> rudolf.first >> rudolf.second;
    for(int i=1; i<=p; i++) {
        int s;
        cin >> s;
        cin >> santa[s].first >> santa[s].second;
        is_alive[s] = true;
        vst[santa[s].first][santa[s].second] = true;
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