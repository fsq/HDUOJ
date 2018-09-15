#include "../stdc++.h"

int n;

VVI e;
VI M, vis, d;
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
        int x = q.front(); q.pop();
        if (d[x] < d[0])
            for (auto y : e[x])
                if (d[M[y]]==INF) {
                    d[M[y]] = d[x] + 1;
                    q.push(M[y]);
                }
    }
    return d[0] != INF;
}

bool dfs(int x) {
    if (x==0) return true;
    int dx = d[x];
    d[x] = INF;
    for (auto y : e[x])
        if (d[M[y]]==dx+1 && dfs(M[y])) {
            M[x] = y;
            M[y] = x;
            return true;
        }
    return false;
}

int main() {
    while (scanf("%d", &n)!=EOF) {
        e.clear();
        e.resize(n+1);
        M = vis = d = VI(n+1);

        for (int x, y, m, i=0; i<n; ++i) {
            scanf("%d: (%d)", &x, &m);
            ++x;
            FOR(j, m) {
                scanf("%d", &y);
                e[x].PB(y+1);
            }
        }

        int ans = 0;
        while (bfs()) 
            REP(i, 1, n)
                if (!M[i] && dfs(i))
                    ++ans;
        printf("%d\n", n-ans);
    }
    
    return 0;
}