#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <deque>
#include <stack>
#include <numeric>
#include <memory>
#include <list>
#include <climits>
#include <fstream>
#include <sstream>
#include <random>
#include <functional>

#define PB                  push_back
#define F                   first
#define S                   second

#define REP(i,from,to)      for(auto i=(from); i<=(to); ++i)
#define PER(i,from,to)      for(auto i=(from); i>=(to); --i)
#define REP_IF(i,from,to,assert)   for(auto i=(from); i<=(to); ++i) if (assert)

#define FOR(i,less_than)    for (auto i=0; i<(less_than); ++i)
#define FORI(i, container)  for (auto i=0; i<(container).size(); ++i)
#define FORI_IF(i, container, assert) for (auto i=0; i<(container).size(); ++i) if (assert)
#define ROFI(i, container)  for (auto i=(container).size()-1; i>=0; --i)

#define FOREACH(elem, container)  for (auto elem : (container))
#define MEMSET(container, value)  memset(container, value, sizeof(container))
#define FILL(container, value)    fill(container.begin(), container.end(), value)
#define FILL0(container)          fill(container.begin(), container.end(), 0)
#define ALL(container)            (container).begin(), (container).end()
#define SZ(container)             (int)((container).size())

#define BACK(set_map)       *prev((set_map).end(), 1)
#define FRONT(set_map)      *(set_map).begin()

using PII = std::pair<int,int>;
using LL  = long long;
using VI  = std::vector<int>;
using VLL = std::vector<LL>;
using VVI = std::vector<VI>;

using namespace std;

int n;
VVI e;
VI done, match, d;
vector<string> abrev;
const int INF = 0x3f3f3f3f;

void findSeq(const string& s, vector<string>& ans, string& now, int i) {
    if (i==s.size()) {
        if (now.size() && now.size()<=4) ans.PB(now);
    } else {
        if (now.size()>4) return;
        findSeq(s, ans, now, i+1);
        now.PB(s[i]);
        findSeq(s, ans, now, i+1);
        now.pop_back();
    }
}

vector<string> simplify(const string& s) {
    vector<string> ans;
    string now;
    findSeq(s, ans, now, 0);
    return ans;
}

bool bfs() {
    FILL(d, INF);
    queue<int> q;
    REP(i, 1, n)
        if (!done[i]) {
            d[i] = 0;
            q.push(i);
        }
    while (q.size()) {
        int x = q.front(); q.pop();
        if (d[x] < d[0])
            for (auto y : e[x])
                if (d[match[y]]==INF) {
                    d[match[y]] = d[x] + 1;
                    q.push(match[y]);
                }
    }
    return d[0] != INF;
}

bool dfs(int x) {
    if (x==0) return true;
    int dx = d[x];
    d[x] = INF;
    for (auto y : e[x])
        if (d[match[y]]==dx+1 && dfs(match[y])) {
            done[x] = y;
            match[y] = x;
            return true;
        }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    ifstream in("input.txt");

    in >> n;
    e.resize(n+1);

    string w;
    abrev.resize(1);
    unordered_map<string, int> ind;
    REP(i, 1, n) {
        in >> w;
        auto simpl = simplify(w);
        for (auto& s : simpl) {
            if (!ind.count(s)) {
                abrev.PB(s);
                ind[s] = abrev.size() - 1;
            } 
            e[i].PB(ind[s]);
        }
    }
    in.close();

    done.resize(n+1);
    match.resize(abrev.size());
    d.resize(n+1);

    int ans = 0;
    while (bfs()) 
        REP(i, 1, n) 
            if (!done[i] && dfs(i))
                ++ans;

    ofstream out("output.txt");
    if (ans==n) {
        REP(i, 1, n) out << abrev[done[i]] << '\n';
    } else 
        out << "-1\n";

    return 0;
}