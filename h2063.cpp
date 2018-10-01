#include "stdc++.h"

int k, n, m;

VVI e;
VI M, d;

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
                if (d[M[v]] == INF) {
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
    while (true) {
        cin >> k;
        if (k==0) break;
        cin >> n >> m;

        M = VI(n+m+1);
        e = VVI(n+1);
        d = VI(n+1);
        for (int u,v,i=0; i<k; ++i) {
            cin >> u >> v;
            e[u].PB(v+n);
        }


        int match = 0;
        while (bfs())
            REP(i, 1, n) 
                match += !M[i] && dfs(i);

        cout << match << endl;
    }
    return 0;
}