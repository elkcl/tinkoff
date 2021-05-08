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
    Node *l = nullptr, *r = nullptr;

    Node(int _key, int _pr): val{_key}, pr{_pr} {}

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

        if (k >= t->val) {
            auto&& [t1, t2] = split(t->r, k);
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

    static pp split_right(Node *t, int k) {
        if (!t)
            return {nullptr, nullptr};

        if (k > t->val) {
            auto&& [t1, t2] = split_right(t->r, k);
            t->r = t1;
            upd(t);
            return {t, t2};
        } else {
            auto&& [t1, t2] = split_right(t->l, k);
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
            t1->r = merge(t1->r, t2);
            upd(t1);
            return t1;
        } else {
            t2->l = merge(t1, t2->l);
            upd(t2);
            return t2;
        }
    }

    static Node* min(Node* t) {
        if (!t)
            return nullptr;
        if (!t->l)
            return t;
        return min(t->l);
    }

    static Node* max(Node* t) {
        if (!t)
            return nullptr;
        if (!t->r)
            return t;
        return max(t->r);
    }
};

struct TreapVec {
    Node *root = nullptr;
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

    [[nodiscard]] bool contains(int x) const {
        if (!root)
            return false;
        auto curr = root;
        while (curr->val != x) {
            if (x < curr->val) {
                if (!curr->l)
                    return false;
                curr = curr->l;
            } else {
                if (!curr->r)
                    return false;
                curr = curr->r;
            }
        }
        return true;
    }

    void insert(int x) {
        if (contains(x))
            return;
        Node *t = new Node(x, dist(mt));
        if (!root) {
            root = t;
            return;
        }
        auto&& [t1, t2] = Node::split(root, x);
        root = Node::merge(t1, Node::merge(t, t2));
    }

    bool erase(int x) {
        if (!root)
            return false;
        auto&& [t12, t3] = Node::split(root, x);
        auto&& [t1, t2] = Node::split_right(t12, x);
        root = Node::merge(t1, t3);
        if (t2) {
            delete t2;
            return true;
        } else {
            return false;
        }
    }

    [[nodiscard]] Node* lower_bound(int x) const {
        if (!root)
            return nullptr;
        auto curr = root;
        Node *last = nullptr;
        while (curr) {
            if (x <= curr->val) {
                last = curr;
                curr = curr->l;
            } else {
                curr = curr->r;
            }
        }
        return last;
    }

    [[nodiscard]] Node* upper_bound(int x) const {
        if (!root)
            return nullptr;
        auto curr = root;
        Node *last = nullptr;
        while (curr) {
            if (x < curr->val) {
                last = curr;
                curr = curr->l;
            } else {
                curr = curr->r;
            }
        }
        return last;
    }

    Node* prev(Node* t) {
        if (!root)
            return nullptr;
        if (!t)
            return nullptr;
        auto&& [t1, t2] = Node::split_right(root, t->val);
        auto ans = Node::max(t1);
        root = Node::merge(t1, t2);
        return ans;
    }

    Node* next(Node* t) {
        if (!root)
            return nullptr;
        if (!t)
            return nullptr;
        auto&& [t1, t2] = Node::split(root, t->val);
        auto ans = Node::min(t2);
        root = Node::merge(t1, t2);
        return ans;
    }

    [[nodiscard]] Node* min() const {
        return Node::min(root);
    }

    [[nodiscard]] Node* max() const {
        return Node::max(root);
    }

    Node* kth(int k, Node* curr = nullptr) {
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
    }
};

int main() {
    fast_io

    TreapVec t;
    int n;
    cin >> n;
    int size = 0;
    for (int q = 0; q < n; ++q) {
        int type, x;
        cin >> type >> x;
        if (type == 1) {
            if (!t.contains(x)) {
                ++size;
                t.insert(x);
            }
        } else if (type == -1) {
            --size;
            t.erase(x);
        } else if (type == 0) {
            Node* ans = t.kth(size - x);
            cout << ans->val << '\n';
        }
    }
}