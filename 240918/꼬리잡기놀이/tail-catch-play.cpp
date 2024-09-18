#include <bits/stdc++.h>
#define endl '\n'
#define ff first
#define ss second
#define INF 987654321
#define int long long
using namespace std;
using pii = pair<int,int>;

const int MAXN = 20+7;
const int MAXM = 5+7;

int ans;
int t;
int team_num;
int n, m, k;
int a[MAXN][MAXN];
int vst[MAXN][MAXN];
int team_vst[MAXM];
int dr[4] = {0, -1, 0, 1}; 
int dc[4] = {1, 0, -1, 0};
bool is_range(int r, int c) {
    return r>=1 && r<=n && c>=1 && c<=n;
}
void check_vst(int r, int c) {
    bool tmp_vst[MAXN][MAXN];
    memset(tmp_vst, false, sizeof tmp_vst);
    
    queue<pii> q;
    q.push(pii(r, c));
    vst[r][c] = team_num;
    while(q.size()) {
        auto [r, c] = q.front();
        q.pop();
        for(int i=0; i<4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(!is_range(nr, nc)) continue;
            if(a[nr][nc] == 0) continue;
            if(vst[nr][nc]) continue;
            
            vst[nr][nc] = team_num;
            q.push(pii(nr,nc));
        }
    }
}
pii find_what(int r, int c, int what) {
    bool tmp_vst[MAXN][MAXN];
    memset(tmp_vst, false, sizeof tmp_vst);
    
    queue<pii> q;
    q.push(pii(r, c));
    tmp_vst[r][c] = true;
    while(q.size()) {
        auto [r, c] = q.front();
        q.pop();
        for(int i=0; i<4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(!is_range(nr, nc)) continue;
            if(a[nr][nc] == 0) continue;
            if(a[nr][nc] == what) {
                return pii(nr, nc);
            }
            if(tmp_vst[nr][nc]) continue;
            
            tmp_vst[nr][nc] = true;
            q.push(pii(nr,nc));
        }
    }
    
    return pii(-1, -1);
}
pii find_head(int r, int c) {
    return find_what(r, c, 1);
}
pii find_tail(int r, int c) {
    return find_what(r, c, 3);
}
pii find_first_4(int r, int c) {
    return find_what(r, c, 4);
}
pii find_first_2(int r, int c) {
    return find_what(r, c, 2);
}
void move_head(pii head) {
    auto [r, c] = head;
    auto [nr, nc] = find_first_4(r, c);
    
    a[nr][nc] = 1;
    a[r][c] = 2;
}
void move_tail(pii tail) {
    auto [r, c] = tail;
    auto [nr, nc] = find_first_2(r, c);
    
    a[nr][nc] = 3;
    a[r][c] = 4;
}
void move(int r, int c) {
    team_num++;
    
    pii head = find_head(r, c);
    pii tail = find_tail(r, c);
    
    move_tail(tail);
    move_head(head);
    
    check_vst(r, c);
}
int dir;
pii find_ball_started() {
   // round 1 == t가 0일때
   // 여기가 좀 헷갈려 ㅠㅠ
   int turn = (t%(4*n)); 
   
   if((turn/n) == 0) {
       dir = 0;
       return pii((turn%n)+1, 1);
   } else if((turn/n) == 1) {
       dir = 1;
       return pii(n, (turn%n)+1);
   } else if((turn/n) == 2) {
       dir = 2;
       return pii(n-(turn%n), n);
   } else {
       dir = 3;
       return pii(1, n-(turn%n));
   }
}
void get_score(pii curr) {
    bool tmp_vst[MAXN][MAXN];
    memset(tmp_vst, false, sizeof tmp_vst);
    
    auto [r, c] = find_head(curr.ff, curr.ss);
    
    int cnt = 1;
    queue<pii> q;
    q.push(pii(r,c));
    tmp_vst[r][c] = true;
    while(q.size()) {
        auto [r, c] = q.front();
        q.pop();
        
        if(r == curr.ff && c == curr.ss) {
            break;
        }
        
        for(int i=0; i<4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(!is_range(nr, nc)) continue;
            if(a[nr][nc] == 0) continue;
            if(a[nr][nc] == 4) continue;
            if(tmp_vst[nr][nc]) continue;
            if(a[nr][nc] == 3) continue; // 꼬리와 머리가 이어져있음...
            
            tmp_vst[nr][nc] = true;
            cnt++;
            
            q.push(pii(nr, nc));
        }
    }
    
    if(a[curr.ff][curr.ss] == 3) {
        cnt++;    
    }
    
    ans += (cnt*cnt); 
}
void change_dir(pii curr) {
    pii head = find_head(curr.ff, curr.ss);
    pii tail = find_tail(curr.ff, curr.ss);
    
    a[head.ff][head.ss] = 3;
    a[tail.ff][tail.ss] = 1;
}
void throw_ball() {
    auto [r, c] = find_ball_started();
    
    // while(is_range(r, c)) {
    //     if(a[r][c] == 0 || a[r][c] == 4|| team_vst[vst[r][c]]) {
    //         r = r + dr[dir];
    //         c = c + dc[dir];
    //     } else {
    //         team_vst[vst[r][c]] = true; 
    //         get_score(pii(r, c));
    //         change_dir(pii(r, c));
    //         break;
    //     }
    // }
    while(is_range(r, c)) {
        if(a[r][c] != 0 && a[r][c] != 4) {
           get_score(pii(r,c)); 
           change_dir(pii(r,c));
           break;
        }    
        r = r + dr[dir];
        c = c + dc[dir];
    }
}
void go_round() {
    memset(vst, 0, sizeof vst);
    team_num = 0;
    memset(team_vst, false, sizeof team_vst);
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            if(vst[i][j]) continue;
            if(a[i][j] == 0) continue;
            move(i, j);
        }
    }
    // cout << "******" << endl;
    // for(int i=1; i<=n; i++) {
    //     for(int j=1; j<=n; j++) {
    //         cout << a[i][j] << ' ';
    //     }
    //     cout << endl;
    // }
    // cout << "******" << endl;
    if(team_num != m) {
        exit(-1);
    }
    
    throw_ball();
}
signed main(void) {
    cin >> n >> m >> k;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            cin >> a[i][j];
        }
    }
    
    while(k--) {
        go_round();   
        t++;
    }
    
    cout << ans << endl;
}