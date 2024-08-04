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

const int MAX = 2000 + 7;
const int GOODS_MAX = 30007;
const int INF = 987645321;


int n, m;
int start;
vector<pii> adj[MAX];
vector<int> dp;
pii goods[30007]; // 여행상품(수익, 목적지)

auto compare = [](const pii& a, const pii& b) {
        if (a.first == b.first) {
            return a.second > b.second;
        }
        return a.first < b.first;
};

priority_queue<pii, vector<pii>, decltype(compare)> use(compare);
bool used[GOODS_MAX];
void init() {
    start = 1; // 초기에는 1부터 시작.
    dp = vector<int>(MAX, INF);
    
    cin >> n >> m;
    vector<vector<int>> tmp_adj(MAX, vector<int>(MAX, INF));
    for(int i=1; i<=m; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        
        // 1-index
        v++;
        u++;
        
        tmp_adj[v][u] = min(tmp_adj[v][u], w);
        tmp_adj[u][v] = min(tmp_adj[u][v], w);
    }
    
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            if(tmp_adj[i][j] != INF) {
                adj[i].push_back(pii(j, tmp_adj[i][j]));
            }
        }
    }
}

void dijkstra() {
    dp = vector<int>(MAX, INF);
    
    dp[start] = 0;
    
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push(pii(0, start));
    
    while(pq.size()) {
        auto [cost, curr] = pq.top();
        pq.pop();
        
        if(dp[curr] != cost)
            continue;
            
        for(auto nxt : adj[curr]) {
            auto [to, weight] = nxt;
            if(dp[curr] + weight < dp[to]) {
                dp[to] = dp[curr] + weight;
                pq.push(pii(dp[to], to));
            }
        }
    }
    
    
    vector<pii> tmp;
    while(use.size()) {
        auto [cost, id] = use.top();
        use.pop();
        
        auto [revenue, dest ] = goods[id];
        tmp.push_back(pii(revenue-dp[dest], id));
    }
    for(auto& elem : tmp) {
        auto [profit, id] = elem;
        use.push(pii(profit, id));
    }
}

void add_goods() {
    int id, revenue, dest;
    cin >> id >> revenue >> dest;
    
    dest++;
    
    goods[id] = pii(revenue, dest);
    used[id] = true;
    use.push(pii(revenue-dp[dest], id));
}

void remove_goods(int id) {
    if(id < 0) return;
    used[id] = false;
}

void remove_goods() {
    int id;
    cin >> id;
    
    remove_goods(id);
}

void sell_goods() {
    int sold_out = -1;
    
    while(use.size()) {
        auto [profit, id] = use.top();
        if(!used[id]) {
            use.pop();
            continue;
        }
        if(profit < 0) break;
        
        use.pop();
        
        
        sold_out = id;
        break;
    }
    
    remove_goods(sold_out); 
    cout << sold_out << endl;
}

void change_start() {
    int s;
    cin >> s;
    
    s++;
    
    start = s;
    dijkstra();
}

void solve() {
    int code;
    cin >> code;
    
    switch(code) {
        case 100:
            init();
            dijkstra();
            break;
        case 200:
            add_goods();
            break;
        case 300:
            remove_goods();
            break;
        case 400:
            sell_goods();
            break;
        case 500:
            change_start();
            break;
    }
}
// 6:35 start
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    
    int q;
    cin >> q;
    while(q--) {
        solve();
    }

    return 0;
}