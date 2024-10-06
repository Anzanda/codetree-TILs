/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <cstring>
#include <queue>
#define endl '\n'
using namespace std;

const int MAXN = 100+7;

int experiment = 0;
int n, k;
int a[MAXN*2];
int moving[MAXN*2];
bool vst[MAXN*2];
queue<int> q;
void rotate() {
    int tmp[MAXN*2];
    tmp[1] = moving[2*n];
    for(int i=1; i<=2*n; i++) {
        tmp[i+1] = moving[i];
    }
    memcpy(moving, tmp, sizeof moving);
    
    queue<int> new_q;
    while(q.size()) {
        new_q.push(q.front()+1);
        q.pop();
    }
    while(new_q.size()) {
        q.push(new_q.front());
        new_q.pop();
    }
    
}
void move() {
    queue<int> new_q;
    while(q.size()) {
        int loc = q.front();
        q.pop();
        // 무빙워크 칸의 번호
        
        if(loc == n) {
            vst[moving[loc]] = false;
            continue;
        }
        if(vst[moving[loc+1]] || a[moving[loc+1]] == 0) {
            continue;
        }
        
        vst[moving[loc]] = false;
        a[moving[loc+1]] -= 1;
        if(loc+1 == n) {
            continue;
        }
        
        vst[moving[loc+1]] = true;
        new_q.push(moving[loc+1]);
    }
    while(new_q.size()) {
        q.push(new_q.front());
        new_q.pop();
    }
}
void add_human() {
    if(vst[moving[1]]) return;
    if(a[moving[1]] == 0) return;
    
    vst[moving[1]] = true;
    a[moving[1]] -= 1;
    q.push(1);
}
bool is_finished() {
    int cnt = 0;
    for(int i=1; i<=2*n; i++) {
        if(a[i] == 0)  cnt++;
    }
    return (cnt >= k) ;
}
void print_moving() {
    printf("=== moving walk! ===\n");
    for(int i=1; i<=n; i++) {
        printf("%d ", moving[i]);
    }
    printf("\n");
    for(int i=2*n; i>=n+1; i--) {
        printf("%d ", moving[i]);
    }
    printf("\n");
}
void print_q() {
    queue<int> tmp;
    int i = 1;
    while(q.size()) {
        int curr = q.front();
        printf("people%d: %d\n", i++, curr);
        tmp.push(q.front()); 
        q.pop();
    }
    while(tmp.size()) {
        q.push(tmp.front());
        tmp.pop();
    }
}
void print_a() {
    for(int i=1; i<=2*n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}
void go() {
    while(!is_finished()) {
        experiment++;
        rotate();
        move();
        add_human();
    }
}
int main()
{
    cin >> n >> k;
    for(int i=1; i<=2*n; i++) {
        cin >> a[i];
        moving[i] = i;
    }

    go();
    printf("%d\n", experiment);
    return 0;
}