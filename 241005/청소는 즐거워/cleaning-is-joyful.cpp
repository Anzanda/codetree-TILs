/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
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
using namespace std;
using pii = pair<int,int>;

const int MAXN = 499+7;
int dr[4] = {0, 1, 0, -1};
int dc[4] = {-1, 0, 1, 0};
// 좌 하 우 상


int ans;

int n;
int a[MAXN][MAXN];
pii loc;
int dir = 0;

int stride = 1;
int stride_left = 1;
int stride_inc_left = 1;
void move() {
    int r, c;
    tie(r, c) = loc;
    
    int nr = r + dr[dir];
    int nc = c + dc[dir];
    
    loc = pii(nr,nc);
    
    stride_left--;   
}
bool is_range(int r, int c) {
    return r>=1 && r<=n && c>=1 && c<=n;
}
int dust;
void record(int nr, int nc, double per) {
    int r, c;
    tie(r, c) = loc;
    if(!is_range(nr, nc)) {
        ans += (int)(a[r][c] * per);
    } else {
        a[nr][nc] += (int)(a[r][c] * per); 
    }
    dust += (int)(a[r][c] * per);
}
void calc() {
    dust = 0;
    int r, c;
    int nr, nc;
    
    tie(r, c) = loc;
    
    nr = r + dr[dir]*2;
    nc = c + dc[dir]*2;
    record(nr, nc, 0.05);
    
    nr = r + dr[(dir+1+4)%4];
    nc = c + dc[(dir+1+4)%4];
    record(nr, nc, 0.07);
    
    nr = r + dr[(dir+1+4)%4]*2;
    nc = c + dc[(dir+1+4)%4]*2;
    record(nr, nc, 0.02);
    
    nr = r + dr[(dir+3+4)%4];
    nc = c + dc[(dir+3+4)%4];
    record(nr, nc, 0.07);
    
    nr = r + dr[(dir+3+4)%4]*2;
    nc = c + dc[(dir+3+4)%4]*2;
    record(nr, nc, 0.02);
    
    nr = r + dr[(dir+1+4)%4] + dr[dir];
    nc = c + dc[(dir+1+4)%4] + dc[dir];
    record(nr, nc, 0.10);
    
    nr = r + dr[(dir+3+4)%4] + dr[dir];
    nc = c + dc[(dir+3+4)%4] + dc[dir];
    record(nr, nc, 0.10);
    
    
    nr = r + dr[(dir+1+4)%4] + dr[(dir+2+4)%4];
    nc = c + dc[(dir+1+4)%4] + dc[(dir+2+4)%4];
    record(nr, nc, 0.01);
    
    nr = r + dr[(dir+3+4)%4] + dr[(dir+2+4)%4];
    nc = c + dc[(dir+3+4)%4] + dc[(dir+2+4)%4];
    record(nr, nc, 0.01);
    
    
    
    nr = r + dr[dir];
    nc = c + dc[dir];
    if(!is_range(nr, nc)) {
        ans += (a[r][c] - dust);
    } else {
        a[nr][nc] += (a[r][c] - dust);
    }
    
    a[r][c] = 0;
}
void turn() {
    if(stride_left != 0) return; 
    if(stride_inc_left == 0) {
        stride_inc_left = 2;
        stride++;
    }
    
    dir = (dir+1+4)%4;
    
    stride_left = stride;
    
    stride_inc_left--;
}
void print_field() {
    printf("==== print field!!! ===\n");
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}
void go() {
    while(!(loc.ff == 1 && loc.ss == 1)) {
        move();
        calc();
        turn();
    }
    // print_field();
}
int main(void) {
    cin >> n;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            cin >> a[i][j];
        }
    }
    loc = pii(n/2+1, n/2+1);
    
    go();
    
    printf("%d\n", ans);
}