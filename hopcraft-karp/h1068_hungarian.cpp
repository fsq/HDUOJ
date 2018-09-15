#include "../stdc++.h"

int n;

VVI e;
VI M, vis;

bool dfs(int x) {
    if (x==0) return true;
    vis[x] = true;
    for (auto y : e[x])
        if (!vis[M[y]] && dfs(M[y])) {
            M[x] = y;
            M[y] = x;
            return true;
        }
    return false;
}

int main() {
    while (scanf("%d", &n)!=EOF) {
        e.clear(), M.clear(), vis.clear();
        e.resize(n+1), M.resize(n+1), vis.resize(n+1);

        for (int x, y, m, i=0; i<n; ++i) {
            scanf("%d: (%d)", &x, &m);
            ++x;
            FOR(j, m) {
                scanf("%d", &y);
                e[x].PB(y+1);
            }
        }

        int ans = 0;
        REP(i, 1, n) {
            FILL0(vis);
            if (!M[i] && dfs(i))
                ++ans;
        }
        printf("%d\n", n-ans);
    }
    
    return 0;
}