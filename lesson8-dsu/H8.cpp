#pragma GCC optimize("Ofast")

#include <iostream>
#include <vector>
#include <numeric>
#include <functional>
#include <algorithm>
#include <utility>
#include <string>

using namespace std;
using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    /*freopen("cutting.in", "r", stdin);
    freopen("cutting.out", "w", stdout);*/

    int n;
    cin >> n;
    vi a(2*n+1, 0);
    for (int i = 1; i < 2*n+1; i += 2) {
        cin >> a[i];
    }
    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        cin >> order[i];
        --order[i];
    }
    reverse(order.begin(), order.end());

    vi dsu(2*n+1);
    iota(dsu.begin(), dsu.end(), 0);
    vi size(2*n+1, 1);
    vi sum(a);
    vi ans;

    function<int(int)> findSet = [&dsu, &findSet](int v) -> int {
        if (v == dsu[v]) return v;
        return dsu[v] = findSet(dsu[v]);
    };
    auto mergeSets = [&dsu, &size, &findSet, &sum](int a, int b) {
        a = findSet(a);
        b = findSet(b);
        if (a != b) {
            if (size[a] < size[b]) swap(a, b);
            dsu[b] = a;
            size[a] += size[b];
            sum[a] += sum[b];
        }
    };

    ll curr = 0;
    ans.push_back(curr);
    for (int i = 0; i < n-1; ++i) {
        int pos = 2*order[i] + 1;
        mergeSets(pos, pos-1);
        mergeSets(pos, pos+1);
        curr = max(curr, sum[findSet(pos)]);
        ans.push_back(curr);
    }
    reverse(ans.begin(), ans.end());

    for (auto it : ans) {
        cout << it << '\n';
    }
}