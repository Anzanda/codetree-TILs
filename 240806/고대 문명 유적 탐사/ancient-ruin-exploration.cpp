/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
using pii = pair<int,int>;


const int MAX = 300 + 7;

// 20:48
int n = 5;
int k, m;
int a[10][10];
int p[MAX];
void rotate(int r, int c) {
    vector<int> tmp;
    int dr[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int dc[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
    for(int i=0; i<8; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        
        tmp.push_back(a[nr][nc]);
    }
    
    for(int i=0; i<8; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        int ni = (i + 8 - 2) %8;
        
        a[nr][nc] = tmp[ni];
    }
}

int ans;
bool is_range(int r, int c) {
    return r>=1 && r<=n && c>=1 && c<=n;
}
bool updated;
bool used[10][10];
bool vst[10][10];
void bfs(int i, int j) {
    int dr[4] = {1, 0, -1, 0};
    int dc[4] = {0, 1, 0, -1};
    
    int ret = 0;
    vector<pii> cand;
    
    queue<pii> q;
    q.push(pii(i, j));
    while(q.size()) {
        auto [r, c] = q.front();
        q.pop();
        if(vst[r][c]) continue;
        
        cand.push_back(pii(r,c));
        vst[r][c] = true;
        ret++;
        
        for(int i=0; i<4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(!is_range(nr, nc)) continue;
            if(vst[nr][nc]) continue;
            if(a[nr][nc] != a[r][c]) continue;
            
            q.push(pii(nr, nc));
        }
    }
    if(ret >= 3) {
        for(auto &elem : cand) {
            auto [r, c] = elem;
            used[r][c] = true; 
        } 
        ans += ret;
        updated = true;
    }
}
int curr_pi;
int p_i;
void update_a() {
    for(int j=1; j<=5; j++) {
        for(int i=5; i>=1; i--) {
            if(!used[i][j]) continue;
            a[i][j] = p[p_i++];
            used[i][j] = false;
        }
    }
}
// 시뮬레이션
void gogo() {
    ans = 0;
    p_i = curr_pi;
    
    updated = true;
    while(updated) {
        updated = false;
        memset(vst, false, sizeof vst);
        for(int i=1; i<=n; i++) {
            for(int j=1; j<=n; j++) {
                if(vst[i][j]) continue;
                bfs(i, j);
            }
        }
        update_a();
    }
}
int total_ans;
int tmp_a[10][10];
void letsgo() {
    // (i, j)를 중심으로 하고, k번 회전!
    int pipi = 100;
    int ii = 100;
    int jj = 100;
    int kk = 100;
    total_ans = 0;
    
    for(int i=2; i<=4; i++) {
        for(int j=2; j<=4; j++) {
            for(int k=1; k<=3; k++) {
                rotate(i, j);
                memcpy(tmp_a, a, sizeof tmp_a);
                gogo();
                memcpy(a, tmp_a, sizeof a);
                if(total_ans < ans) {
                    ii = i;
                    jj = j;
                    kk = k;
                    pipi = p_i;
                    total_ans = ans;
                }
                if(total_ans == ans) {
                    if(kk > k) {
                        ii = i;
                        jj = j;
                        kk = k;
                        pipi = p_i;
                        total_ans = ans;
                    }
                    if(kk == k) {
                        if(jj > j) {
                            ii = i;
                            jj = j;
                            kk = k;
                            pipi = p_i;
                            total_ans = ans;
                        }
                        if(jj == j) {
                            if(ii > i) {
                               ii = i;
                               jj = j;
                               kk = k;
                            pipi = p_i;
                                total_ans = ans;
                            }
                        }
                    }
                }
            }
            rotate(i, j); // 원상복구!
        }
    }
    if(total_ans == 0) {
        k = 0;
        return;
    }
    
    for(int i=1; i<=kk; i++) {
        rotate(ii, jj); 
    }
    gogo();
    curr_pi = pipi;
    cout << total_ans << ' ';
    
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    
    cin >> k >> m;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            cin >> a[i][j];
        }
    }
    for(int i=1; i<=m; i++) {
        cin >> p[i];
    }
    
    curr_pi = 1;
    while(k--) {
        letsgo();
    }
    

    return 0;
}