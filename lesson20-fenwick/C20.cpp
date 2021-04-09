//#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <functional>

using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;

template<typename T>
struct fenwick3 {
    int size;
    vector<vector<vector<T>>> f;

    explicit fenwick3(int n): size{n} {
        f.resize(n+1, vector<vector<T>>(n+1, vector<T>(n+1, 0)));
    }

    T sum(int k1, int k2, int k3) {
        T ans = 0;
        for (int i = k1; i > 0; i -= i & -i)
            for (int j = k2; j > 0; j -= j & -j)
                for (int k = k3; k > 0; k -= k & -k)
                    ans += f[i][j][k];
        return ans;
    }

    T sum(int l1, int l2, int l3, int r1, int r2, int r3) {
        return sum(r1, r2, r3) - (sum(l1-1, r2, r3) + sum(r1, l2-1, r3) + sum(r1, r2, l3-1)
        - sum(l1-1, l2-1, r3) - sum(l1-1, r2, l3-1) - sum(r1, l2-1, l3-1)
        + sum(l1-1, l2-1, l3-1));
    }

    void upd(int k1, int k2, int k3, T x) {
        for (int i = k1; i <= size; i += i & -i)
            for (int j = k2; j <= size; j += j & -j)
                for (int k = k3; k <= size; k += k & -k)
                    f[i][j][k] += x;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    fenwick3<ll> f(n);
    for (;;) {
        int t;
        cin >> t;
        switch (t) {
            case 1:
                int x, y, z;
                ll k;
                cin >> x >> y >> z >> k;
                f.upd(x+1, y+1, z+1, k);
                break;
            case 2:
                int x1, y1, z1, x2, y2, z2;
                cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
                cout << f.sum(x1+1, y1+1, z1+1, x2+1, y2+1, z2+1) << '\n';
                break;
            default:
                return 0;
        }
    }
}