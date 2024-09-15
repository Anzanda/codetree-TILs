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

const int MAXN = 10+7;
const int MAXM = 10+7;


int ans;
int N, M, K;
int maze[MAXN][MAXN];
pii loc[MAXM];
bool is_alive[MAXM];
pii e;

// 상, 하, 좌, 우
bool is_range(int r, int c) {
    return r>=1 && r<=N && c>=1 && c<=N;
}

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1}; 
int get_distance(pii a, pii b) {
    return abs(a.first-b.first) + abs(a.second-b.second);
}
int get_direction(int curr) {
    int ret = -1;
    
    auto [r, c] = loc[curr];
    
    int min_dist = get_distance(loc[curr], e);    
    for(int i=0; i<4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(!is_range(nr, nc)) continue;
        if(maze[nr][nc] > 0) continue;
        
        int dist = get_distance(pii(nr, nc), e);
        if(dist < min_dist) {
            min_dist = dist; 
            ret = i;
        }
    }
    
    return ret;
}
void move(int curr) {
    int direction = get_direction(curr);
    if(direction == -1) return;
    
    ans++;
    
    auto [r, c] = loc[curr];
    int nr = r + dr[direction];
    int nc = c + dc[direction];
    
    loc[curr] = pii(nr, nc);
    if(get_distance(loc[curr], e) == 0) {
        is_alive[curr] = false;
    }
}
int get_min_len_of_square() {
    int min_len = 987654321;
   for(int i=1; i<=M; i++) {
       if(!is_alive[i]) continue;
       
       int len = max(abs(loc[i].first-e.first), abs(loc[i].second-e.second));
       min_len = min(min_len, len);
   } 
   
   return min_len;
}
bool is_square_ok(int r, int c, int len) {
    int user_count = 0;
    int exit_count = 0;
    for(int i=r; i<=r+len; i++) {
        for(int j=c; j<=c+len; j++) {
            if(!is_range(i, j)) return false;
            for(int k=1; k<=M; k++) {
                if(!is_alive[k]) continue;
                if(i == loc[k].first && j == loc[k].second) {
                    user_count++;
                } 
            }
            if(i == e.first && j == e.second) {
                exit_count++;
            }
        }    
    }
    if(exit_count == 0) return false;
    if(user_count == 0) return false;
    
    return true;
}
pii get_square(int len) {
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            if(is_square_ok(i, j, len)) {
                return pii(i, j);
            }
        }
    }
    // error
    return pii(-1, -1);
}
void rotate() {
    int len = get_min_len_of_square();  
    
    auto [r, c] = get_square(len);
     
    int new_maze[MAXN][MAXN];
    pii new_loc[MAXM];
    pii new_e;
    memcpy(new_maze, maze, sizeof new_maze);
    memcpy(new_loc, loc, sizeof new_loc);
    
    int ii=r;
    int jj=c;
    for(int j=c; j<=c+len; j++) {
        for(int i=r+len; i>=r; i--) {
            new_maze[ii][jj] = maze[i][j];
            for(int k=1; k<=M; k++) {
                if(!is_alive[k]) continue;
                if(i == loc[k].first && j == loc[k].second) {
                    new_loc[k].first = ii;
                    new_loc[k].second = jj;
                }
            }
            if(i == e.first && j == e.second) {
                new_e.first = ii;
                new_e.second = jj;
            }
            jj++; 
        }
        jj = c;
        ii++;
    }
    for(int i=r; i<=r+len; i++) {
        for(int j=c; j<=c+len; j++) {
            if(new_maze[i][j] > 0) {
                new_maze[i][j]--;
            }
        }
    }
    
    
    memcpy(maze, new_maze, sizeof maze);
    memcpy(loc, new_loc, sizeof loc);
    e.first = new_e.first;
    e.second = new_e.second;
}
bool is_done() {
    for(int i=1; i<=M; i++) {
        if(is_alive[i]) return false;
    }
    return true;
}
void go_second() {
    if(is_done()) {
        K = 0;
    }
    for(int i=1; i<=M; i++) {
        if(!is_alive[i]) continue;
        move(i);
    }
    if(is_done()) {
        K = 0;
    }
    
    rotate();
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M >> K;
    for(int i=1; i<=N; i++) {
       for(int j=1; j<=N; j++) {
           cin >> maze[i][j];
       } 
    }
    for(int i=1; i<=M; i++) {
        cin >> loc[i].first >> loc[i].second;
        is_alive[i] = true;
    }
    cin >> e.first >> e.second;
    
    while(K--) {
        go_second();
    }
    
    cout << ans << endl;
    cout << e.first << " " << e.second << endl;
    
    // cout << endl;
    // cout << endl;
    // for(int i=1; i<=N; i++) {
    //     for(int j=1; j<=N; j++) {
    //         cout << maze[i][j] << ' ';
    //     }
    //     cout << endl;
    // }
    
    // cout << endl;
    
    // for(int i=1; i<=M; i++) {
    //     cout << loc[i].first << ", " << loc[i].second << endl;
    // }
    // cout << "exit: " << e.first << ", " << e.second << endl;
    return 0;
}