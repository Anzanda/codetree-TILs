#include <bits/stdc++.h>
#define endl '\n'
#define ff first
#define ss second
#define INF 987654321
using namespace std;
using pii = pair<int,int>;

const int MAXM = 10000*7;

int t;
int ans;
int n, m, h, k;
bool is_dead[MAXM];
pii run[MAXM];
int run_dir[MAXM];
int run_dir_mode[MAXM];
pii tree[MAXM];

// 개어지럽다...
pii tagger;
bool is_tagger_in; // 밖에서 안으로 움직이냐
int tagger_dir;
int tagger_left;
int tagger_move_max;
int tagger_rotate_cnt;
// 상 우 하 좌
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

bool is_range(int r, int c) {
    return r>=1 && r<=n && c>=1 && c<=n;
}
bool can_move(int curr) {
    auto [r1, c1] = run[curr];
    auto [r2, c2] = tagger;
    
    int dist = abs(r1-r2) + abs(c1-c2);
    return (dist <= 3);
}
// 반대로 돌았기 때문에 항상 range를 만족함. (n>=5)
pii _move(int r, int c, int i) {
    int nr = r + dr[i];
    int nc = c + dc[i];
    
    if(nr == tagger.ff && nc == tagger.ss) {
        return pii(r, c);
    } else {
        return pii(nr, nc);
    }
}
void move_runner(int curr) {
    if(is_dead[curr]) return;
    if(!can_move(curr)) {
        return; 
    }
    
    auto [r, c] = run[curr];
    
    int dir = run_dir[curr];
    int nr = r + dr[dir];
    int nc = c + dc[dir];
    
    if(!is_range(nr, nc)) {
        run_dir[curr] = (run_dir[curr] + 4 + 2)%4;
    }
    
    run[curr] = _move(r, c, run_dir[curr]);
}
// 됐다고 믿자
void move_tagger() {
    auto [r, c] = tagger;
    
    int nr = r + dr[tagger_dir];
    int nc = c + dc[tagger_dir];
    tagger = pii(nr, nc);
    tagger_left--;
    
    if(nr == 1 && nc == 1) {
        tagger_dir = 2;
        tagger_left = n-1;
        tagger_move_max = n-1;
        tagger_rotate_cnt = -1; // (1,1)일때는 n-1로 3번 가더라고...
        is_tagger_in = true;
    }
    if(nr == (n/2 + 1) && nc == (n/2 + 1) && tagger_dir == 2) {
        tagger_dir = 0;
        tagger_left = 1;
        tagger_move_max = 1;
        tagger_rotate_cnt = 0;
        is_tagger_in = false;
    }
    if(tagger_left == 0) {
        if(is_tagger_in) tagger_dir = (tagger_dir+4-1)%4;
        else             tagger_dir = (tagger_dir+4+1)%4;
        tagger_rotate_cnt++;
        
        if(tagger_rotate_cnt == 2) {
            if(is_tagger_in) tagger_move_max--;
            else tagger_move_max++;
            tagger_rotate_cnt = 0;
        }
        tagger_left = tagger_move_max;
    }
}
void do_tag() {
    auto [r, c] = tagger;
    int dir = tagger_dir;
    int cnt = 3;
    while(cnt--) {
        bool is_con = false;
        for(int i=1; i<=h; i++) {
            if(tree[i].ff == r && tree[i].ss == c) {
                is_con = true;
            }
        }
        if(is_con) {
            r = r + dr[dir];
            c = c + dc[dir];
            continue;
        }
        
        for(int i=1; i<=m; i++) {
            if(is_dead[i]) continue;
            if(run[i].ff == r && run[i].ss == c) {
                ans += t;
                is_dead[i] = true;
            }
        }
        
        r = r + dr[dir];
        c = c + dc[dir];
    }
}
void go_turn() {
    for(int i=1; i<=m; i++) {
        move_runner(i);
    }
     move_tagger();
     do_tag();
    //  printf("when turn%d: (%d, %d) | %d\n", t, tagger.ff, tagger.ss, tagger_dir);
}
int main(void) {
    cin >> n >> m >> h >> k;
    for(int i=1; i<=m; i++) {
        cin >> run[i].ff >> run[i].ss >> run_dir_mode[i];
        // 상 우 하 좌
        if(run_dir_mode[i] == 1) { // 좌우
            run_dir[i] = 1;
        } else { // 상하
            run_dir[i] = 2;
        }
    }
    for(int i=1; i<=h; i++) {
        cin >> tree[i].ff >> tree[i].ss;
    }
    tagger = pii(n/2+1, n/2+1);
    tagger_dir = 0;
    tagger_left = 1;
    tagger_move_max = 1;
    tagger_rotate_cnt = 0;
    while(k--) {
        t++;
        go_turn();
    }
    cout << ans << endl;
}