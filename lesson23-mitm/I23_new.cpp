#pragma GCC optimize("O3")
#pragma GCC target("avx2")

#include <iostream>
#include <utility>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <functional>
#include <string>

using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;
using ui = unsigned int;

void karatsuba(vi::iterator a, vi::iterator b, vi::iterator c, int n) {
    if (n <= 64) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                c[i + j] += a[i] * b[j];
            }
        }
    } else {
        int k = n / 2;
        vi tl(k, 0), tr(k, 0), t(n, 0);
        for (int i = 0; i < k; ++i) {
            tl[i] = a[i] + a[i + k];
            tr[i] = b[i] + b[i + k];
        }

        karatsuba(tl.begin(), tr.begin(), t.begin(), k);
        karatsuba(a, b, c, k);
        karatsuba(a + k, b + k, c + n, k);

        auto t1 = t.begin();
        auto t2 = t.begin() + k;
        auto p11 = c;
        auto p12 = c + k;
        auto p21 = c + n;
        auto p22 = c + n + k;

        for (int i = 0; i < k; ++i) {
            int c1 = p12[i] + t1[i] - p11[i] - p21[i];
            int c2 = p21[i] + t2[i] - p12[i] - p22[i];
            c[i + k] = c1;
            c[i + n] = c2;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("multiply.in", "r", stdin);
    freopen("multiply.out", "w", stdout);

    string n, m;
    cin >> n >> m;
    bool positive = true;
    if (n[0] == '-') {
        positive = !positive;
        n.erase(0, 1);
    }
    if (m[0] == '-') {
        positive = !positive;
        m.erase(0, 1);
    }

    vi a, b;
    for (int i = n.size() - 1; i >= 0; --i) {
        a.push_back(n[i] - '0');
    }
    for (int i = m.size() - 1; i >= 0; --i) {
        b.push_back(m[i] - '0');
    }

    int digc = static_cast<int>(pow(2, ceil(log2(max(a.size(), b.size())))));
    a.insert(a.end(), digc - a.size(), 0);
    b.insert(b.end(), digc - b.size(), 0);

    vi c(digc * 2, 0);
    karatsuba(a.begin(), b.begin(), c.begin(), digc);
    int carry = 0;
    for (int i = 0; i < c.size(); ++i) {
        c[i] += carry;
        carry = c[i] / 10;
        c[i] %= 10;
    }
    while (*(c.end() - 1) == 0 && c.end() - 1 != c.begin())
        c.pop_back();

    if (!positive && *(c.end() - 1) != 0) cout << '-';
    for (int i = c.size() - 1; i >= 0; --i) {
        cout << c[i];
    }
    cout << '\n';
}