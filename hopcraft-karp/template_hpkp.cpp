// lg1640, O(sqrt(V)logV * E)


#include "../stdc++.h"

const int MAXN = 10003;
const int INF = 0x3f3f3f3f;
VVI e(MAXN);
VI done, M, d;

bool bfs(int n) {
    queue<int> q;
    FILL(d, INF);
    REP(i, 1, n)
        if (!done[i]) {
            q.push(i);
            d[i] = 0;
        } 

    while (!q.empty()) {
        int x=q.front(); q.pop();
        if (d[x] < d[0])
            FOREACH(y, e[x])
                if (d[M[y]]==INF) {
                    d[M[y]] = d[x] + 1;
                    q.push(M[y]);
                }
    }
    return d[0] != INF;
}

bool dfs(int x) {
    if (x==0) return true;
    int dx=d[x]; 
    d[x] = INF;
    FOREACH(y, e[x])
        if (d[M[y]]==dx+1 && dfs(M[y])) {
            M[y] = x, done[x] = y;
            return true;
        }
    return false;
}

bool canMatch(int n) {
    FILL0(done), FILL0(M);
    int ans = 0;
    // build a layer graph in each iteration, then try to match new nodes
    while (bfs(n)) 
        REP(i, 1, n)
            if (!done[i] && dfs(i)) 
                ++ans;

    return ans == n;
}

int main() {
    ios::sync_with_stdio(false);
    int n=0, m;
    cin >> m;
    for (int x,y,i=1; i<=m; ++i) {
        cin >> x >> y;
        e[x].PB(i), e[y].PB(i);
        n = max(n, max(x, y));
    }

    done.resize(n+1), d.resize(n+1);
    M.resize(m+1);

    // binary search for the max n s.t. [1..n] can be matched
    int l=0, r=n;
    while (l<r) {
        int mid = (l+r) >> 1;
        if (canMatch(mid)) {
            if (l+1 == r) {
                if (canMatch(r)) ++l;
                break;
            }
            l = mid;
        } else 
            r = mid - 1;
    }
    cout << l << endl;
    return 0;
}