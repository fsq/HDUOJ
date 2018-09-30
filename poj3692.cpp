#include <vector>
#include <queue>
#include <iostream>
#include <cstring>

#define PB                  push_back
#define F                   first
#define S                   second

#define REP(i,from,to)      for(int i=(from); i<=(to); ++i)
#define PER(i,from,to)      for(int i=(from); i>=(to); --i)
#define REP_IF(i,from,to,assert)   for(int i=(from); i<=(to); ++i) if (assert)

#define FOR(i,less_than)    for (int i=0; i<(less_than); ++i)
#define FORI(i, container)  for (int i=0; i<(container).size(); ++i)
#define FORI_IF(i, container, assert) for (int i=0; i<(container).size(); ++i) if (assert)
#define ROFI(i, container)  for (int i=(container).size()-1; i>=0; --i)

#define MEMSET(container, value)  memset(container, value, sizeof(container))
#define FILL(container, value)    fill(container.begin(), container.end(), value)
#define ALL(container)            (container).begin(), (container).end()
#define SZ(container)             (int)((container).size())

using namespace std;
// #include "stdc++.h"

int n, m, k;

int know[505][505];
vector<vector<int> > e;
int M[505];
int d[505];
const int INF = 0x3f3f3f3f;

bool hg(int u) {
    if (u==0) return true;
    d[u] = true;
    for (int i=0; i<e[u].size(); ++i) {
        int v = e[u][i];
        if (!d[M[v]] && hg(M[v])) {
            M[u] = v;
            M[v] = u;
            return true;
        }
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
            know[u][v] = 1;
        }

        e = vector<vector<int> >(n+1);
        REP(i, 1, n)
            REP(j, 1, m)
                if (!know[i][j]) 
                    e[i].PB(n+j);
                

        int match = 0;
        MEMSET(M, 0);
        REP(i, 1, n) 
            if (!M[i]) {
                MEMSET(d, 0);
                if (hg(i)) 
                    ++match;
            }
        cout << "Case "<<test<<": "<<n+m - match << '\n';

    }
    return 0;
}