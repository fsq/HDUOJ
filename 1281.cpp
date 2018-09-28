#include "stdc++.h"

int n, m, k;
VVI e;
VI d, M;
const int INF = 0x3f3f3f3f;

bool bfs() {
    queue<int> q;
    FILL(d, INF);
    REP(i, 1, n)
        if (!M[i]) {
            d[i] = 0;
            q.push(i);
        }

    while (!q.empty()) {
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
    if (u==0) return true;
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

bool dfs1(int u) {
    if (u==0) return true;
    d[u] = true;
    FOREACH(v, e[u])
        if (!d[M[v]] && dfs1(M[v])) 
            return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    int t = 0;
    while (cin >> n >> m >> k) {
        ++t;
        e.clear(), M.clear();
        e.resize(n+m+1);
        M.resize(n+m+1);
        d.resize(n+m+1);
        for (int u,v,i=0; i<k; ++i) {
            cin >> u >> v;
            e[u].PB(v+n);
            e[v+n].PB(u);
        }

        int match = 0;
        while (bfs()) 
            REP(i, 1, n) 
                match += !M[i] && dfs(i);

        int ans = 0;
        REP(u, 1, n)
            if (M[u]) {
                int t = M[u]; M[u] = M[t] = 0;
                FILL(d, 0);
                bool found = false;

                FOREACH(x, e[t])
                    if (x!=u && dfs1(M[x])) {
                        found = true;
                        break;
                    }
                if (!found)
                    FOREACH(v, e[u])
                        if (v!=t && dfs1(M[v])) {
                            found = true;
                            break;
                        }  
                ans += found;         
                M[u] = t, M[t] = u;
            }
        cout << "Board "<<t<<" have "<<match-ans<<" important blanks for "<<match<<" chessmen.\n";
    }

    return 0;
}