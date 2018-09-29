#include "stdc++.h"

int n, m, k, t;

VI d;
vector<PII> e;

int main() {
    ios::sync_with_stdio(false);

    cin >> t;
    while (t--) {
        cin >> n >> m >> k;
        e.clear();
        d = VI(n+m+1);
        for (int u,v,i=0; i<k; ++i) {
            cin >> u >> v;
            v += n;
            e.PB({u, v});
            ++d[u], ++d[v];
        }

        LL ans = 0;
        FOREACH(&p, e)
            ans += ((LL)d[p.first]-1) * ((LL)d[p.second]-1);
        cout << ans * 2 << endl;
    }
    return 0;
}