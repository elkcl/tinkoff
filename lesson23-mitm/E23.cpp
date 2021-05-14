#ifndef ONPC
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <functional>
#include <cassert>

using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONPC
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#else
#define file_io(x)
#endif

struct point {
    ll x, y;
};

ll mind = INT64_MAX;
ll ans_a_x;
ll ans_a_y;
ll ans_b_x;
ll ans_b_y;

vector<point> v;
vector<point> buf;

bool operator<(const point &a, const point &b) {
    return a.y < b.y;
}

bool comp_x(const point &a, const point &b) {
    if (a.x == b.x)
        return a.y < b.y;
    else
        return a.x < b.x;
}

void upd(const point &a, const point &b) {
    ll dist = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    if (dist < mind) {
        mind = dist;
        ans_a_x = a.x;
        ans_a_y = a.y;
        ans_b_x = b.x;
        ans_b_y = b.y;
    }
}

void closest(/*vector<point> &v, vector<point> &buf, */int l, int r) {
    if (r - l <= 10) {
        for (int i = l; i < r; ++i)
            for (int j = i + 1; j < r; ++j)
                upd(v[i], v[j]);
        sort(v.begin() + l, v.begin() + r);
        return;
    }

    int m = (l + r) >> 1;
    ll mx = v[m].x;
    closest(/*v, buf, */l, m);
    closest(/*v, buf, */m, r);
    merge(v.begin() + l, v.begin() + m, v.begin() + m, v.begin() + r, buf.begin());
    copy(buf.begin(), buf.begin() + r - l, v.begin() + l);

    int b_cnt = 0;
    for (int i = l; i < r; ++i) {
        if ((v[i].x - mx) * (v[i].x - mx) < mind) {
            for (int j = b_cnt - 1; j >= 0 && ((v[i].y - buf[j].y) * (v[i].y - buf[j].y) < mind); --j) {
                upd(v[i], buf[j]);
            }
            buf[b_cnt++] = v[i];
        }
    }
}

int main() {
    fast_io
    //file_io("rendezvous")

    int n;
    cin >> n;
    /*vector<point> v(n);
    vector<point> buf(n);*/
    v.resize(n);
    buf.resize(n);
    for (int i = 0; i < n; ++i) {
        ll x, y;
        cin >> x >> y;
        v[i] = {x, y};
    }
    sort(all(v), comp_x);
    closest(/*v, buf,*/ 0, n);

    cout << ans_a_x << ' ' << ans_a_y << '\n';
    cout << ans_b_x << ' ' << ans_b_y << '\n';
}