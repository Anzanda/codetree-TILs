/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <tuple>
#include <queue>
#include <cstring>
#define endl '\n'
#define ff first
#define ss second
using namespace std;
using pii = pair<int,int>;

const int MAXN = 20+7;

int ans;
int n, m;
int a[MAXN][MAXN];
// 우, 하, 좌, 상
int dr[4] = {0, 1, 0, -1};
int dc[4] = {1, 0, -1, 0};
int dice_num = 1;
int dice_next[4] = {3, 2, 4, 5};
pii dice = pii(1,1);
int dir;
bool is_range(int r, int c) {
    return r>=1&&r<=n&&c>=1&&c<=n;
}
void change_dice_num() {
    int new_dice_num = dice_next[(dir+4+2)%4];
    
    int new_dice_next[4] = {0, 0, 0, 0};
    new_dice_next[dir] = dice_num;
    new_dice_next[(dir+4+2)%4] = (7-dice_num);
    new_dice_next[(dir+4+1)%4] = dice_next[(dir+4+1)%4];
    new_dice_next[(dir+4+3)%4] = dice_next[(dir+4+3)%4];
    
    
    dice_num = new_dice_num;
    for(int i=0; i<4; i++) {
        dice_next[i] = new_dice_next[i];
    }
}
void move() {
    int r, c;
    tie(r,c) = dice;
    
    int nr, nc;
    nr = r + dr[dir];
    nc = c + dc[dir];
    
    if(!is_range(nr, nc)) {
        dir = (dir + 2 + 4)%4;
        nr = r + dr[dir];
        nc = c + dc[dir];
    }
    
    change_dice_num();
    
    dice = pii(nr, nc);
}
int dist[MAXN][MAXN];
void get_score() {
    memset(dist, -1, sizeof dist);
    
    queue<pii> q;
    q.push(dice);
    int cnt = 1;
    int xx = a[dice.ff][dice.ss];
    dist[dice.ff][dice.ss] = 0;
    while(q.size()) {
        int r, c;
        tie(r,c) = q.front();
        q.pop();
        
        for(int i=0; i<4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(!is_range(nr, nc)) {
                continue;
            }
            if(dist[nr][nc] != -1) {
                continue;
            }
            if(a[nr][nc] != xx) {
                continue;
            }
            dist[nr][nc] = dist[r][c] + 1;
            cnt += 1;
            q.push(pii(nr,nc));
        }
    }
    
    ans += (cnt * xx);
}
void change_dir() {
    int r, c;
    tie(r, c) = dice;
    
    int xx = (7-dice_num);
    if(xx > a[r][c]) {
        dir = (dir+4+1)%4;
    } else if(xx < a[r][c]) {
        dir = (dir+4-1)%4;
    } else {
        dir = dir;
    }
}
void go() {
    move();
    get_score();
    change_dir();
}
int main()
{
    cin >> n >> m;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            cin >> a[i][j];
        }
    }
    
    while(m--) {
        go();
        // printf("dice: (%d, %d)\n", dice.ff, dice.ss);
        // printf("dice_num: %d\n", dice_num);
        // for(int i=0; i<4; i++) {
        //     printf("%d ", dice_next[i]);
        // }
        // printf("\n");
    }
    printf("%d\n", ans);
    return 0;
}