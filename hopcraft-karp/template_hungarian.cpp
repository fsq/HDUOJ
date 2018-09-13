// lg1640, O(VE)
// build a n by m bipartite graph
// left: numbers right: gear id

#include "../stdc++.h"

const int MAXN = 10003;
VVI e(MAXN);
VI match;
VI vis(MAXN);
int m;

bool dfs(int x) {
    if (x==0) return true;
    // if x fails to find an aug path, we will not visit x again
    vis[x] = true;
    for (auto y : e[x])
        if (!vis[match[y]] && dfs(match[y])) {
            match[y] = x;
            return true;
        }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> m;
    for (int x,y,i=1; i<=m; ++i) {
        cin >> x >> y;
        e[x].PB(i), e[y].PB(i);
    }

    match.resize(m+1);

    int ans = 0;
    REP(i, 1, MAXN) {
        FILL(vis, 0);
        // [1..i-1] are matched, [i..n] are unmatched
        // now try to find an aug path starting from i to match i
        if (dfs(i))
            ++ans;
        else
            break;
    }
    cout << ans << endl;
    
    return 0;
}