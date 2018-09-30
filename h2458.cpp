#include "stdc++.h"

int n, m, k;

int know[505][505];
VVI e;
int M[505];
int d[505];
const int INF = 0x3f3f3f3f;

bool bfs() {
    MEMSET(d, 0x3f);
    queue<int> q;
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

int main() {
    ios::sync_with_stdio(false);
    int test = 0;
    while (true) {
        cin >> n >> m >> k;
        ++test;
        if (!n && !m && !k) break;

        MEMSET(know, 0);

        for (int u,v,i=0; i<k; ++i) {
            cin >> u >> v;
            know[u][v] =  1;
        }

        e = VVI(n+m+1);
        REP(i, 1, n)
            REP(j, 1, m)
                if (!know[i][j]) {
                    e[i].PB(n+j);
                    e[n+j].PB(i);
                }

        int match = 0;
        MEMSET(M, 0);
        while (bfs())
            REP(i, 1, n)
                if (!M[i] && dfs(i))
                    ++match;
        
        cout << "Case "<<test<<": "<<n+m - match << '\n';

    }
    return 0;
}