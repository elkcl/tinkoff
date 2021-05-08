#ifndef ONPC
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#endif

#include <iostream>
#include <utility>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <functional>
#include <string>
#include <numeric>
#include <set>
#include <array>
#include <optional>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;
using ui = unsigned int;
using k_set = tree<
        int,
        null_type,
        less<>,
        rb_tree_tag,
        tree_order_statistics_node_update
        >;

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONPC
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#else
#define file_io(x)
#endif



int main() {
    fast_io

    k_set t;
    int n;
    cin >> n;
    for (int q = 0; q < n; ++q) {
        int type, x;
        cin >> type >> x;
        if (type == 1) {
            t.insert(x);
        } else if (type == -1) {
            t.erase(x);
        } else if (type == 0) {
            cout << *t.find_by_order(t.size() - x) << '\n';
        }
    }
}