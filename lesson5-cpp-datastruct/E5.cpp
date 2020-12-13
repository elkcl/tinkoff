#pragma GCC optimize("O3")

#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using ui = unsigned int;

const ui N = 1u << 24u;
using vll = vector<ll>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    vll delta(N, 0);
    int m, q;
    ui a, b;
    ui cur = 0;
    cin >> m >> q >> a >> b;
    auto nextRand = [a, b, &cur]() {
        cur = cur * a + b;
        return cur >> 8u;
    };

    for (int i = 0; i < m; ++i) {
        ui add = nextRand();
        ui l = nextRand();
        ui r = nextRand();
        if (l > r) swap(l, r);

        delta[l] += add;
        if (r != N-1) delta[r+1] -= add;
    }

    for (int i = 1; i < N; ++i) {
        delta[i] += delta[i-1];
    }
    for (int i = 1; i < N; ++i) {
        delta[i] += delta[i-1];
    }

    ui ans = 0;
    for (int i = 0; i < q; ++i) {
        ui l = nextRand();
        ui r = nextRand();
        if (l > r) swap(l, r);

        if (l == 0) {
            ans += delta[r];
        } else {
            ans += delta[r] - delta[l-1];
        }
    }

    cout << ans << "\n";
}