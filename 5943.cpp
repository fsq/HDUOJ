#include "stdc++.h"

VI d, M;
VVI e;
int t, n, s;
const int INF = 0x3f3f3f3f;

bool bfs() {
    FILL(d, INF);
    queue<int> q;
    REP(i, 1, n)
        if (!M[i]) {
            d[i] = 0;
            q.push(i);
        }
    while (q.size()) {
        int u = q.front(); q.pop();
        if (d[u] < d[0]) 
            FOREACH(v, e[u])
                if (d[M[v]]==INF) {
                    d[M[v]] = d[u] + 1;
                    q.push(M[v]);
                }
    }
    return d[0] != INF;
}

bool dfs(int u) {
    if (!u) return true;
    int du = d[u];
    d[u] = INF;
    FOREACH(v, e[u]) 
        if (d[M[v]]==du+1 && dfs(M[v])) {
            M[u] = v;
            M[v] = u;
            return true;
        }
    
    return false;
}

bool perfect(int s, int n) {
    e = VVI(n+1);
    REP(u, s+1, s+n)
        REP(v, 1, n)
            if (u%v==0) 
                e[u-s].PB(n+v);
    d = VI(n+1);
    M = VI(2*n+1);

    int match = 0;
    while (bfs()) 
        REP(i, 1, n)
            if (!M[i] && dfs(i))
                ++match;        
    
    return match == n;
}

int main() {
    cin >> t;
    REP(c, 1, t) {
        cin >> n >> s;
        if (s+1 <= n) swap(s, n);
        cout << "Case #" << c << ": ";
        if (n>300 || !perfect(s, n)) 
            cout << "No\n";
        else
            cout << "Yes\n";
    }
    return 0;
}