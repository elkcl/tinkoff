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
    int val, pr;
    Node *l = nullptr, *r = nullptr;

    Node(int _key, int _pr): val{_key}, pr{_pr} {}

    static pp split(Node *t, int k) {
        if (!t)
            return {nullptr, nullptr};

        if (k >= t->val) {
            auto&& [t1, t2] = split(t->r, k);
            t->r = t1;
            return {t, t2};
        } else {
            auto&& [t1, t2] = split(t->l, k);
            t->l = t2;
            return {t1, t};
        }
    }

    static pp split_right(Node *t, int k) {
        if (!t)
            return {nullptr, nullptr};

        if (k > t->val) {
            auto&& [t1, t2] = split_right(t->r, k);
            t->r = t1;
            return {t, t2};
        } else {
            auto&& [t1, t2] = split_right(t->l, k);
            t->l = t2;
            return {t1, t};
        }
    }

    static Node* merge(Node *t1, Node *t2) {
        if (!t1)
            return t2;
        if (!t2)
            return t1;

        if (t1->pr > t2->pr) {
            t1->r = merge(t1->r, t2);
            return t1;
        } else {
            t2->l = merge(t1, t2->l);
            return t2;
        }
    }

    static pp min(Node* t, Node* p = nullptr) {
        if (!t)
            return {nullptr, nullptr};
        if (!t->l)
            return {t, p};
        return min(t->l, t);
    }

    static pp max(Node* t, Node* p = nullptr) {
        if (!t)
            return {nullptr, nullptr};
        if (!t->r)
            return {t, p};
        return max(t->r, t);
    }
};

struct TreapVec {
    Node *root = nullptr;
    random_device rd;
    mt19937 mt;
    uniform_int_distribution<int> dist{1, 1'000'000'000};

    TreapVec(): mt{777} {}

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
        auto&& [t1, t2] = Node::split(root, x);
        auto&& [t, p] = Node::max(t1);
        if (t && t->val == x) {
            if (p) {
                p->r = t->l;
            } else {
                t1 = t->l;
            }
            delete t;
            root = Node::merge(t1, t2);
            return true;
        }
        root = Node::merge(t1, t2);
        return false;
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
        auto&& [ans, ignore] = Node::max(t1);
        root = Node::merge(t1, t2);
        return ans;
    }

    Node* next(Node* t) {
        if (!root)
            return nullptr;
        if (!t)
            return nullptr;
        auto&& [t1, t2] = Node::split(root, t->val);
        auto&& [ans, ignore] = Node::min(t2);
        root = Node::merge(t1, t2);
        return ans;
    }

    [[nodiscard]] Node* min() const {
        return Node::min(root).first;
    }

    [[nodiscard]] Node* max() const {
        return Node::max(root).first;
    }
};

int main() {
    fast_io

    TreapVec t;
    string q;
    int x;
    while (cin >> q) {
        cin >> x;
        if (q == "insert") {
            t.insert(x);
        } else if (q == "delete") {
            t.erase(x);
        } else if (q == "exists") {
            if (t.contains(x))
                cout << "true\n";
            else
                cout << "false\n";
        } else if (q == "next") {
            Node* ans = t.upper_bound(x);
            if (ans)
                cout << ans->val << '\n';
            else
                cout << "none\n";
        } else if (q == "prev") {
            Node* low = t.lower_bound(x);
            Node* ans;
            if (!low) {
                ans = t.max();
            } else {
                ans = t.prev(low);
            }
            if (ans)
                cout << ans->val << '\n';
            else
                cout << "none\n";
        } else {
            break;
        }
    }
}