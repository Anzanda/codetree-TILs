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
#include <algorithm>
#include <tuple>
#include <cstring>
#include <set>
#define endl '\n'
#define ff first
#define ss second
#define int long long
using namespace std;
using pii = pair<int,int>;

const int MAXN = 20+7;
const int MAXNN = MAXN*MAXN;
int dr[4] = {1, 0, -1, 0};
int dc[4] = {0, 1, 0, -1};

int n;
int a[MAXN][MAXN];
set<int> friends[MAXNN];
queue<int> q;
bool is_range(int r, int c) {
   return r>=1 && r<=n && c>=1 && c<=n; 
}
int get_near_friends(int curr, int r, int c) {
    int ret = 0 ;
    for(int i=0; i<4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(!is_range(nr, nc)) continue; 
        if(a[nr][nc] == 0) continue;
        if(friends[curr].find(a[nr][nc]) != friends[curr].end()) {
            ret += 1;
        }
    }    
    return ret;
}
vector<pii> find_most_friends(int curr) {
    vector<pii> cands;
    
    int max_num = -1;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            if(a[i][j] != 0) continue; // 무조건 빈칸중에 들어가!
            int num = get_near_friends(curr, i, j); 
            max_num = max(max_num, num);
        }
    }
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            if(a[i][j] != 0) continue; // 무조건 빈칸중에 들어가!
            int num = get_near_friends(curr, i, j); 
            if(max_num == num) {
                cands.push_back(pii(i, j));
            }
        }
    }
    
    return cands;
}
int get_empty_cells(int r, int c) {
    int ret = 0;
    for(int i=0; i<4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(!is_range(nr, nc)) continue;
        if(a[nr][nc] == 0) ret++;
    }
    return ret;
}
vector<pii> find_most_empty_cells(vector<pii> cands) {
    vector<pii> ret;
    
    int max_num = -1;
    for(pii cand : cands) {
        int r,c;
        tie(r,c) = cand;
        int num = get_empty_cells(r, c);
        max_num = max(max_num, num);
    }
    for(pii cand : cands) {
        int r,c;
        tie(r,c) = cand;
        int num = get_empty_cells(r, c);
        if(max_num == num) {
            ret.push_back(cand);
        }
    }
    
    return ret;
}
bool compare(pii a, pii b) {
        if(a.ff == b.ff) {
            return a.ss < b.ss;
        }
        return a.ff < b.ff;
}
void print_fields() {
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            printf("%lld ", a[i][j]);
        }
        printf("\n");
    }
}
void go(int curr) {
    vector<pii> cands = find_most_friends(curr);
    vector<pii> cands2 = find_most_empty_cells(cands);
    
    sort(cands2.begin(), cands2.end(), compare);
    
    pii loc = cands2[0];
    a[loc.ff][loc.ss] = curr;
}
signed main(void) {
    cin >> n;
    for(int i=1; i<=n*n; i++) {
        int curr; cin >> curr;
        q.push(curr);
        for(int j=0; j<4; j++) {
            int nxt; cin >> nxt;
            friends[curr].insert(nxt);
        }
    }
    while(q.size()) {
        go(q.front()); 
        q.pop();
    }
    // print_fields();
    int ans = 0;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            int num = get_near_friends(a[i][j], i, j);
            if(num == 0) continue;
            num--;
            int tmp = 1;
            while(num--) {
                tmp *= 10;
            }
            ans += tmp;
            
        }
    }
    printf("%lld\n", ans);
}