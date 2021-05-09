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
#include <cassert>

using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;
using ui = unsigned int;

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONPC
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#else
#define file_io(x)
#endif

struct Node;
using pp = pair<Node*, Node*>;

struct Node {
    ll val;
    int pr, sz = 1;
    ll sum;
    bool rev = false;
    Node *l = nullptr, *r = nullptr;

    Node(ll _key, int _pr): val{_key}, pr{_pr}, sum{_key * _key} {}

    static int get_sz(Node* t) {
        if (!t)
            return 0;
        return t->sz;
    }

    static ll get_sum(Node* t) {
        if (!t)
            return 0;
        return t->sum;
    }

    static void upd(Node* t) {
        if (t) {
            t->sz = 1 + get_sz(t->l) + get_sz(t->r);
            t->sum = t->val * t->val + get_sum(t->l) + get_sum(t->r);
        }
    }

    static void push(Node* t) {
        /*if (!t)
            return;
        if (!(t->rev))
            return;
        swap(t->l, t->r);
        if (t->l)
            t->l->rev ^= 1;
        if (t->r)
            t->r->rev ^= 1;
        t->rev = false;*/
    }

    static pp split(Node *t, int k) {
        if (!t)
            return {nullptr, nullptr};

        push(t);
        int num = get_sz(t->l);
        if (k > num) {
            auto&& [t1, t2] = split(t->r, k - num - 1);
            t->r = t1;
            upd(t);
            return {t, t2};
        } else {
            auto&& [t1, t2] = split(t->l, k);
            t->l = t2;
            upd(t);
            return {t1, t};
        }
    }

    static Node* merge(Node *t1, Node *t2) {
        if (!t1) {
            upd(t2);
            return t2;
        }
        if (!t2) {
            upd(t1);
            return t1;
        }

        if (t1->pr > t2->pr) {
            push(t1);
            t1->r = merge(t1->r, t2);
            upd(t1);
            return t1;
        } else {
            push(t2);
            t2->l = merge(t1, t2->l);
            upd(t2);
            return t2;
        }
    }
};

struct TreapVec {
    Node *root = nullptr;
    int size = 0;
    random_device rd;
    mt19937 mt;
    uniform_int_distribution<int> dist{1, 1'000'000'000};

    TreapVec() {
        ui rrr = rd();
#ifdef ONPC
        //cout << rrr << '\n';
#endif
        mt.seed(3524900925);
    }

    void insert(ll val, int k = -1) {
        assert(k <= size);
        if (k == -1)
            k = size;
        ++size;
        Node *t = new Node(val, dist(mt));
        if (!root) {
            root = t;
            return;
        }
        auto&& [t1, t2] = Node::split(root, k);
        root = Node::merge(t1, Node::merge(t, t2));
    }

    bool erase(int k = -1) {
        assert(k < size);
        if (k == -1)
            k = size - 1;
        --size;
        auto&& [t12, t3] = Node::split(root, k + 1);
        auto&& [t1, t2] = Node::split(t12, k);
        root = Node::merge(t1, t3);
        if (t2) {
            delete t2;
            return true;
        } else {
            return false;
        }
    }

    Node* cut(int l, int r) {
        assert(l <= r);
        assert(r < size);
        size -= r - l + 1;
        auto&& [t12, t3] = Node::split(root, r + 1);
        auto&& [t1, t2] = Node::split(t12, l);
        root = Node::merge(t1, t3);
        return t2;
    }

    void paste(Node* t, int k) {
        assert(k <= size);
        size += Node::get_sz(t);
        auto&& [t1, t2] = Node::split(root, k);
        root = Node::merge(t1, Node::merge(t, t2));
    }

    void to_vec(vll &v, Node* curr) {
        if (!curr)
            return;
        to_vec(v, curr->l);
        v.push_back(curr->val);
        to_vec(v, curr->r);
    }

    void to_vec(vll &v) {
        to_vec(v, root);
    }

    ll sum(int l, int r) {
        if (r < l)
            return 0;
        assert(r < size);
        auto&& [t12, t3] = Node::split(root, r + 1);
        auto&& [t1, t2] = Node::split(t12, l);
        ll res = Node::get_sum(t2);
        root = Node::merge(t1, Node::merge(t2, t3));
        return res;
    }

    void rev(int l, int r) {
        assert(l <= r);
        assert(r < size);
        auto&& [t12, t3] = Node::split(root, r + 1);
        auto&& [t1, t2] = Node::split(t12, l);
        t2->rev ^= 1;
        root = Node::merge(t1, Node::merge(t2, t3));
    }

    ll operator[](int k) {
        assert(k < size);
        auto&& [t12, t3] = Node::split(root, k + 1);
        auto&& [t1, t2] = Node::split(t12, k);
        ll ans = t2->val;
        root = Node::merge(t1, Node::merge(t2, t3));
        return ans;
    }
};

int main() {
    fast_io
    file_io("river")

    int n, _, m;
    cin >> n >> _;
    TreapVec tr;
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        tr.insert(a);
    }
    cin >> m;
    cout << tr.sum(0, tr.size - 1) << '\n';
    for (int q = 0; q < m; ++q) {
        int e, v;
        cin >> e >> v;
        --v;
        if (e == 1) {
            if (v == 0) {
                ll s = tr[0] + tr[1];
                tr.erase(0);
                tr.erase(0);
                tr.insert(s, 0);
            } else if (v == tr.size - 1) {
                ll s = tr[tr.size - 2] + tr[tr.size - 1];
                tr.erase();
                tr.erase();
                tr.insert(s);
            } else {
                ll a1 = tr[v - 1];
                ll a2 = tr[v];
                ll a3 = tr[v + 1];
                ll s1 = a1 + a2 / 2;
                ll s2 = a2 - a2 / 2 + a3;
                tr.erase(v - 1);
                tr.erase(v - 1);
                tr.erase(v - 1);
                tr.insert(s2, v - 1);
                tr.insert(s1, v - 1);
            }
            cout << tr.sum(0, tr.size - 1) << '\n';
        } else if (e == 2) {
            ll a = tr[v];
            ll s1 = a / 2;
            ll s2 = a - a / 2;
            tr.erase(v);
            tr.insert(s2, v);
            tr.insert(s1, v);
            cout << tr.sum(0, tr.size - 1) << '\n';
        }
    }
}