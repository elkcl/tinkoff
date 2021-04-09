#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <numeric>
#include <functional>
#include <algorithm>
#include <utility>

using namespace std;
using vi = vector<int>;

typedef int Vertex;

struct Edge {
    Vertex from, to;
    int w;

    Edge(Vertex _from, Vertex _to, int _w):
        from{_from}, to{_to}, w{_w} {}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Edge> g;
    g.reserve(m);
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        g.emplace_back(a-1, b-1, w);
    }
    sort(g.begin(), g.end(), [](Edge a, Edge b) {
       return a.w < b.w;
    });

    vi dsu(n);
    iota(dsu.begin(), dsu.end(), 0);
    vi rank(n, 0);

    function<int(int)> findSet = [&dsu, &findSet](int v) -> int {
        if (v == dsu[v]) return v;
        return dsu[v] = findSet(dsu[v]);
    };
    auto mergeSets = [&dsu, &rank, &findSet](int a, int b) {
        a = findSet(a);
        b = findSet(b);
        if (a != b) {
            if (rank[a] < rank[b]) swap(a, b);
            dsu[b] = a;
            if (rank[a] == rank[b]) ++rank[a];
        }
    };

    int cost = 0;
    for (auto &edge : g) {
        if (findSet(edge.from) != findSet(edge.to)) {
            cost += edge.w;
            mergeSets(edge.from, edge.to);
        }
    }

    cout << cost << '\n';
}