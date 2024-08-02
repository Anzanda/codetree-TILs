#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

const int MAX = 1e5+7;

int q;
int mid, pid, c, dep;
int p[MAX];
int color[MAX];
int max_dep[MAX];
int curr_dep[MAX];
vector<int> adj[MAX];
bool validate_add_node() {
    int curr = pid;
    int tmp_dep = 1;
    while(curr != -1) {
        if(tmp_dep + 1 > max_dep[curr]) {
            return false;
        }
        tmp_dep += 1;
        curr = p[curr];
    }
    return true;
}
void update_curr_dep_of_parents() {
    int curr = pid;
    while(curr != -1) {
        curr_dep[curr] += 1;
        curr = p[curr];
    }
}
void add_node() {
    cin >> mid >> pid >> c >> dep;
    if(!validate_add_node()) return;

    p[mid] = pid;
    color[mid] = c;
    max_dep[mid] = dep;
    curr_dep[mid] = 1;
    
    update_curr_dep_of_parents();
    adj[pid].push_back(mid);
}

void dfs_color(int curr, int c) {
    color[curr] = c;
    for(auto nxt : adj[curr]) {
        dfs_color(nxt, c);
    }
}
void change_color() {
    cin >> mid >> c;
    dfs_color(mid, c);
}

void get_color() {
    cin >> mid;
    cout << color[mid] << endl;
}


int ans;
set<int> dfs_score(int curr) {
    set<int> ret;
    ret.insert(color[curr]);
    if(adj[curr].size() == 0) {
        ans += 1;
        return ret;
    }

    for(auto nxt : adj[curr]) {
        set<int> tmp(ret);
        set<int> to_union = dfs_score(nxt);
        set_union(tmp.begin(), tmp.end(), to_union.begin(), to_union.end(), inserter(ret, ret.begin()));
    }

    ans += (ret.size() * ret.size());
    return ret;
}
void get_score() {

    ans = 0;
    for(int i=1; i<=MAX; i++) {
        if(p[i] != -1) continue;
        if(adj[i].size() != 0) {
            dfs_score(i);
        }
    }


    cout << ans << endl;
}

void solve() {
    int what;
    cin >> what;
    switch(what) {
        case 100:
            add_node();
            break;
        case 200:
            change_color();
            break;
        case 300:
            get_color();
            break;
        case 400:
            get_score();
            break;
    }
}
int main() {
    cin.tie(0)->sync_with_stdio(0);

    memset(p, -1, sizeof p);

    cin >> q;
    while(q--) {
        solve();
    }
    return 0;
}