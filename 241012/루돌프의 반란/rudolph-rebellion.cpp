/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <tuple>
#include <cstring>
#include <algorithm>
#include <vector>
#define endl '\n'
#define ff first
#define ss second
using namespace std;
using pii = pair<int,int>;

const int MAXN = 50+7;
const int MAXP = 30+7;
const int INF = 987645321;

int ans;

int n,m,p,cc,d;
pii rudolf;
int rudolf_dir;
pii santa[MAXP];
int santa_dir[MAXP];
int score[MAXP];
bool is_dead[MAXP];
int paralyzed[MAXP];

int dr[8] = {-1,-1,-1,0,1,1,1,0};
int dc[8] = {-1,0,1,1,1,0,-1,-1};
void print_score() {
    for(int i=1; i<=p; i++) {
        printf("%d ", score[i]);
    }
    printf("\n");
}
void print_rudolf() {
    printf("rudolf: (%d, %d)\n", rudolf.ff, rudolf.ss);
}
void print_santas() {
    for(int i=1; i<=p; i++) {
        if(is_dead[i]) {
            printf("santa%d is dead!!!\n", i); 
        }
        else {
            printf("santa%d: (%d, %d) | paralyzed: %d\n", i, santa[i].ff, santa[i].ss, paralyzed[i]);
        }
    }
}

int compare(pii &a, pii &b) {
    if(a.ff != b.ff) {
        return a.ff > b.ff;
    }
    return a.ss > b.ss;
}
bool is_range(int r, int c) {
    return r>=1 && r<=n && c>=1 && c<=n;
}

int find_closest_santa() {
    int r, c; tie(r, c) = rudolf;
    int min_dist= INF;
    for(int i=1; i<=p; i++) {
        if(is_dead[i]) continue;
        int nr, nc; tie(nr, nc) = santa[i];
        int dist = (nr-r)*(nr-r) + (nc-c)*(nc-c);
        min_dist = min(min_dist, dist);
    }
    vector<pii> cands;
    for(int i=1; i<=p; i++) {
        if(is_dead[i]) continue;
        int nr, nc; tie(nr, nc) = santa[i];
        int dist = (nr-r)*(nr-r) + (nc-c)*(nc-c);
        if(dist == min_dist) {
            cands.push_back(pii(nr,nc));
        }
    }
    sort(cands.begin(), cands.end(), compare);
    
    pii cand = cands[0];
    for(int i=1; i<=p; i++) {
        if(is_dead[i]) continue;
        int nr, nc; tie(nr, nc) = santa[i];
        if(nr == cand.ff && nc == cand.ss) {
            return i;
        }
    }
     
    return -1;
}
void move_rudolf() {
    int to = find_closest_santa();
    int r, c; tie(r, c) = rudolf;
    int x, y; tie(x, y) = santa[to];
    
    
    int min_dist = INF;
    for(int i=0; i<8; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(!is_range(nr, nc)) continue;
        int dist = (nr-x)*(nr-x) + (nc-y)*(nc-y); 
        min_dist = min(min_dist, dist);
    } 
    
    for(int i=0; i<8; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(!is_range(nr, nc)) continue;
        int dist = (nr-x)*(nr-x) + (nc-y)*(nc-y); 
        if(dist == min_dist) {
            rudolf_dir = i;
            rudolf = pii(nr, nc);
            return;
        }
    } 
}
void interact_with_other(int curr) {
    int r, c; tie(r, c) = santa[curr];
    int next = -1;
    for(int i=1; i<=p; i++) {
        if(is_dead[i]) continue;
        if(i == curr) continue;
        int x, y; tie(x, y) = santa[i];
        if(x== r && y== c) {
            next = i;
            break;
        }
    }
    if(next == -1) return;
    
    int dir = santa_dir[curr];
    tie(r, c) = santa[next];
    
    int nr = r + dr[dir];
    int nc = c + dc[dir];
    santa[next] = pii(nr, nc);
    santa_dir[next] = dir;
    if(!is_range(nr, nc)) {
        is_dead[next] = true;
        return;
    }
    
    interact_with_other(next);
}
void move_santa_by_rudolf(int curr) {
    int r, c; tie(r, c) = santa[curr]; 
    int nr = r + dr[rudolf_dir]*cc;
    int nc = c + dc[rudolf_dir]*cc;
    santa[curr] = pii(nr, nc);
    if(!is_range(nr, nc)) {
        is_dead[curr] = true;
        return;
    }
    
    interact_with_other(curr);
}
void bomb_by_rudolf() {
    int r, c; tie(r, c) = rudolf;
    int curr = -1;
    for(int i=1; i<=p; i++) {
        if(is_dead[i]) continue;
        int x, y;
        tie(x, y) = santa[i];
        if(x == r && y == c) {
            score[i] += cc;
            curr = i;
            santa_dir[i] = rudolf_dir;
            paralyzed[i] = 2;
            break;
        }
    }
    if(curr == -1) {
        return;
    } else {
        move_santa_by_rudolf(curr); 
    }
}
bool is_santa_here(int curr, int r, int c) {
    for(int i=1; i<=p; i++) {
        if(is_dead[i]) continue;
        if(i == curr) continue;
        if(r == santa[i].ff && c == santa[i].ss) {
            return true;    
        }
    } 
    return false;
}
void move_santa(int curr) {
   int r, c; tie(r, c) = santa[curr];
   
   int min_dist = (r-rudolf.ff)*(r-rudolf.ff) + (c-rudolf.ss)*(c-rudolf.ss);
   for(int i=1; i<8; i+=2) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(!is_range(nr, nc)) continue;
        if(is_santa_here(curr, nr, nc)) continue;
        int dist = (nr-rudolf.ff)*(nr-rudolf.ff) + (nc-rudolf.ss)*(nc-rudolf.ss);
        min_dist = min(min_dist, dist); 
   }
   for(int i=1; i<8; i+=2) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(!is_range(nr, nc)) continue;
        if(is_santa_here(curr, nr, nc)) continue;
        int dist = (nr-rudolf.ff)*(nr-rudolf.ff) + (nc-rudolf.ss)*(nc-rudolf.ss);
        if(dist == min_dist) {
            santa[curr] = pii(nr, nc);
            santa_dir[curr] = i;
            return;
        }
   }
}
void bomb_by_santa(int curr) {
    int r, c; tie(r, c) = santa[curr];
    if(r != rudolf.ff || c != rudolf.ss) {
        return; 
    }
    
    score[curr] += d;
    paralyzed[curr] = 2;
    santa_dir[curr] = (santa_dir[curr]+8+4)%8;
    
    int dir = santa_dir[curr];
    int nr = r + dr[dir]*d;
    int nc = c + dc[dir]*d;
    santa[curr] = pii(nr, nc);
    if(!is_range(nr, nc)) {
        is_dead[curr] = true; 
        return;
    }
    
    interact_with_other(curr);
}
void move_santas() {
    for(int i=1; i<=p; i++) {
        if(is_dead[i]) continue;
        if(paralyzed[i] > 0) continue;
        move_santa(i);
        bomb_by_santa(i);
    }
}
void next_round() {
    for(int i=1; i<=p; i++) {
        if(is_dead[i]) continue;
        paralyzed[i] -= 1;
    }
    for(int i=1; i<=p; i++) {
        if(is_dead[i]) continue;
        score[i] += 1;
    }
}
bool is_finished() {
    for(int i=1; i<=p; i++) {
        if(is_dead[i]) continue;
        return false;
    }
    return true;
}
void go() {
    move_rudolf();
    // print_rudolf();
    bomb_by_rudolf();
    move_santas();
    if(is_finished()) {
        m = 0; // ??
        return;
    }
    // print_santas();
    next_round(); 
    // print_score();
}
int main()
{
    cin >> n >> m >> p >> cc >> d;
    cin >> rudolf.ff >> rudolf.ss;
    for(int i=1; i<=p; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        santa[a] = pii(b,c);
    }
    
    while(m--) {
        go();
    }
    print_score();
    return 0;
}