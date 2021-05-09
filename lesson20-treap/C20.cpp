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

const int INF = 1e9 + 1e8;

struct Node;
using pp = pair<Node*, Node*>;

struct Node {
    int val, pr, sz = 1;
    Node *l = nullptr, *r = nullptr, *p = nullptr;

    Node(int _key, int _pr): val{_key}, pr{_pr} {}

    void discl() const {
        if (l)
            l->p = nullptr;
    }

    void discr() const {
        if (r)
            r->p = nullptr;
    }

    void setl(Node* t) {
        l = t;
        if (t)
            t->p = this;
    }

    void setr(Node* t) {
        r = t;
        if (t)
            t->p = this;
    }

    static int get_sz(Node* t) {
        if (!t)
            return 0;
        return t->sz;
    }

    static void upd(Node* t) {
        if (t) {
            t->sz = 1 + get_sz(t->l) + get_sz(t->r);
        }
    }

    static pp split(Node *t, int k) {
        if (!t)
            return {nullptr, nullptr};

        int num = get_sz(t->l);
        if (k > num) {
            t->discr();
            auto&& [t1, t2] = split(t->r, k - num - 1);
            t->setr(t1);
            upd(t);
            return {t, t2};
        } else {
            t->discl();
            auto&& [t1, t2] = split(t->l, k);
            t->setl(t2);
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
            t1->discr();
            t1->setr(merge(t1->r, t2));
            upd(t1);
            return t1;
        } else {
            t2->discl();
            t2->setl(merge(t1, t2->l));
            upd(t2);
            return t2;
        }
    }

    /*static Node* minv(Node* t) {
        if (!t)
            return nullptr;
        if (!t->l)
            return t;
        return minv(t->l);
    }

    static Node* max(Node* t) {
        if (!t)
            return nullptr;
        if (!t->r)
            return t;
        return max(t->r);
    }*/
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

    Node* insert(int val, int k = -1) {
        assert(k <= size);
        if (k == -1)
            k = size;
        ++size;
        Node *t = new Node(val, dist(mt));
        if (!root) {
            root = t;
            return t;
        }
        auto&& [t1, t2] = Node::split(root, k);
        root = Node::merge(t1, Node::merge(t, t2));
        return t;
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

    /*[[nodiscard]] Node* minv() const {
        return Node::minv(root);
    }

    [[nodiscard]] Node* max() const {
        return Node::max(root);
    }*/

    /*Node* kth(int k, Node* curr = nullptr) {
        if (!root)
            return nullptr;
        if (!curr)
            curr = root;
        int num = Node::get_sz(curr->l);
        if (num == k)
            return curr;
        if (num > k)
            return kth(k, curr->l);
        return kth(k - num - 1, curr->r);
    }*/

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

    int index(Node* t) {
        if (!t)
            return -1;
        int ans = Node::get_sz(t->l);
        Node* last = t;
        Node* curr = t->p;
        while (curr) {
            if (last == curr->r)
                ans += Node::get_sz(curr->l) + 1;
            last = curr;
            curr = curr->p;
        }
        return ans;
    }

    template<typename Func>
    void apply(int l, int r, Func f) {
        assert(l <= r);
        assert(r < size);
        auto&& [t12, t3] = Node::split(root, r + 1);
        auto&& [t1, t2] = Node::split(t12, l);
        t2 = f(t2);
        root = Node::merge(t1, Node::merge(t2, t3));
    }

    template<typename Func>
    int get(int l, int r, Func f) {
        assert(l <= r);
        assert(r < size);
        auto&& [t12, t3] = Node::split(root, r + 1);
        auto&& [t1, t2] = Node::split(t12, l);
        int ans = f(t2);
        root = Node::merge(t1, Node::merge(t2, t3));
        return ans;
    }

    void swap(int l1, int r1, int l2, int r2) {
        if (l1 > l2) {
            ::swap(l1, l2);
            ::swap(r1, r2);
        }
        assert(r1 < l2);

        Node *t2 = cut(l2, r2);
        Node *t1 = cut(l1, r1);
        paste(t2, l1);
        paste(t1, l2);
    }
};

int main() {
    fast_io

    int n, m;
    cin >> n >> m;
    TreapVec tr;
    vector<Node*> v(n + 1);
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        v[a] = tr.insert(a);
    }

    for (int q = 0; q < m; ++q) {
        int t;
        cin >> t;
        if (t == 1) {
            int l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;
            tr.swap(l1-1, r1-1, l2-1, r2-1);
        } else if (t == 2) {
            int x;
            cin >> x;
            int k = tr.index(v[x]);
            vi c;
            if (k + 1 == tr.size) {
                cout << "-1 -1 -1 \n";
                continue;
            }
            tr.apply(k + 1, min(k + 3, tr.size - 1), [&tr, &c](Node* t) {
                tr.to_vec(c, t);
                return t;
            });
            for (int el : c)
                cout << el << ' ';
            for (int i = 0; i < 3 - c.size(); ++i)
                cout << "-1 ";
            cout << '\n';
        }
    }
}