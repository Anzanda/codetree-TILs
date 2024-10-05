/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
// 1:04 start
#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
#include <cstring>
#define endl '\n'
#define ff first
#define ss second
using namespace std;
using pii = pair<int,int>;

const int MAXN = 15+7;
const int MAXM = 107;
int dr[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int dc[8] = {1, 1, 0, -1, -1, -1, 0, 1};

int n, m;
int year;
int a[MAXN][MAXN];
pii q[MAXM];
vector<pii> sups;
pii move_sup(pii loc) {
    int d, dir;
    tie(dir, d) = q[year];
    
    int r, c;
    tie(r, c) = loc;
    
    // 이거맞ㄴ나...
    int nr = (r-1 + d*dr[dir] + n) % n + 1;
    int nc = (c-1 + d*dc[dir] + n) % n + 1;
    
    return pii(nr, nc);
    
}
void move_sups() {
    for(int i=0; i<sups.size(); i++) {
        pii new_loc = move_sup(sups[i]);
        sups[i] = new_loc;
    }
}
void inject() {
    for(pii loc : sups) {
        int r, c;
        tie(r, c) = loc;
        a[r][c] += 1;
    }
}
bool is_range(int r, int c) {
    return r>=1 && r<=n && c>=1 && c<=n;
}
void bonus() {
    for(pii loc : sups) {
        int r, c;
        tie(r, c) = loc;
        for(int i=1; i<8; i+=2) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(!is_range(nr, nc)) continue;
            if(a[nr][nc] >= 1) {
                a[r][c] += 1;
            }
        } 
    } 
}
void gen_sups() {
    bool vst[MAXN][MAXN];
    memset(vst, false, sizeof vst);
    
    for(pii loc : sups) {
        int r, c;
        tie(r, c) = loc;
        vst[r][c] = true;
    }
    
    vector<pii> new_sups;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            if(vst[i][j]) continue;
            if(a[i][j] < 2) continue;
            
            a[i][j] -= 2;
            new_sups.push_back(pii(i,j));
        } 
    }
    
    sups = new_sups;
}
void print_sups() {
    printf("==== all sups locaiton ===\n");
    for(pii loc : sups) {
        int r, c;
        tie(r, c) = loc;
        printf("(%d, %d)\n", r, c);
    }
}
void print_fields() {
    printf("==== all tree's height ===\n");
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}
void go() {
   move_sups(); 
//   printf("after move_sups()\n");
//   print_sups();
   inject();
//   printf("after inject()\n");
//   print_fields();
   bonus();
//   printf("afetr bonus()\n");
//   print_fields();
   gen_sups();
//   printf("after gen_sups()\n");
//   print_sups();
//   print_fields();
}
int main(void) {
    cin >> n >> m;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            cin >> a[i][j];
        }
    }
    sups.push_back(pii(n-1,1));
    sups.push_back(pii(n-1,2));
    sups.push_back(pii(n,1));
    sups.push_back(pii(n,2));
    for(int i=1; i<=m; i++) {
        cin >> q[i].ff >> q[i].ss; 
        q[i].ff-=1;
    }
    
    for(int i=1; i<=m; i++) {
        year = i;
        go();
    }
    
    int ans = 0;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            ans += a[i][j]; 
        }
    }
    printf("%d\n", ans);
}