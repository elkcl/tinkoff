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
    int val, pr, sz = 1;
    ll sum;
    bool rev = false;
    Node *l = nullptr, *r = nullptr;

    Node(int _key, int _pr): val{_key}, pr{_pr}, sum{_key} {}

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
            t->sum = t->val + get_sum(t->l) + get_sum(t->r);
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

    void insert(int val, int k = -1) {
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

    bool erase(int k) {
        assert(k < size);
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

    void to_vec(vi &v, Node* curr) {
        if (!curr)
            return;
        to_vec(v, curr->l);
        v.push_back(curr->val);
        to_vec(v, curr->r);
    }

    void to_vec(vi &v) {
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
};

int main() {
    fast_io
    file_io("swapper")

    int n;
    cin >> n;
    int ctr = 1;

    while (n != 0) {
        cout << "Swapper " << ctr << ":\n";

        TreapVec even;
        TreapVec odd;

        int m;
        cin >> m;
        bool flag = true;
        for (int i = 0; i < n; ++i) {
            int a;
            cin >> a;
            if (flag)
                even.insert(a);
            else
                odd.insert(a);
            flag ^= 1;
        }

        for (int q = 0; q < m; ++q) {
            int t;
            cin >> t;
            if (t == 1) {
                int l, r;
                cin >> l >> r;
                --l;
                --r;

                if (l % 2 == 0) {
                    Node *t1 = even.cut(l / 2, (r - 1) / 2);
                    Node *t2 = odd.cut(l / 2, (r - 1) / 2);
                    even.paste(t2, l / 2);
                    odd.paste(t1, l / 2);
                } else {
                    Node *t1 = even.cut((l + 1) / 2, r / 2);
                    Node *t2 = odd.cut((l - 1) / 2, (r - 2) / 2);
                    even.paste(t2, (l + 1) / 2);
                    odd.paste(t1, (l - 1) / 2);
                }
            } else if (t == 2) {
                int l, r;
                cin >> l >> r;
                --l;
                --r;

                int le, lo, re, ro;
                if (l % 2 == 0) {
                    le = lo = l / 2;
                } else {
                    le = (l + 1) / 2;
                    lo = (l - 1) / 2;
                }
                if (r % 2 == 0) {
                    re = r / 2;
                    ro = (r - 2) / 2;
                } else {
                    re = ro = (r - 1) / 2;
                }

                cout << even.sum(le, re) + odd.sum(lo, ro) << '\n';
            }
        }
        cin >> n;
        cout << '\n';
        ++ctr;
    }
}