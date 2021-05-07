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
#include <bitset>

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

const int ALPHABET = 2;
const char FIRST = '0';
const size_t NUMLEN = 32;

struct Node {
    array<int, ALPHABET> next{};
    int term = 0;
};

struct Trie {
    vector<Node> nodes = vector<Node>(1);

    int create_node() {
        nodes.emplace_back();
        return static_cast<int>(nodes.size() - 1);
    }

    void insert(const string &s) {
        int v = 0;
        for (char c : s) {
            c -= FIRST;
            if (!nodes[v].next[c])
                nodes[v].next[c] = create_node();
            v = nodes[v].next[c];
        }
        ++nodes[v].term;
    }

    bool contains(const string &s) const {
        int v = 0;
        for (char c : s) {
            c -= FIRST;
            if (!nodes[v].next[c])
                return false;
            v = nodes[v].next[c];
        }
        return nodes[v].term > 0;
    }

    bool erase(const string &s) {
        int v = 0;
        for (char c : s) {
            c -= FIRST;
            if (!nodes[v].next[c])
                return false;
            v = nodes[v].next[c];
        }
        if (nodes[v].term > 0) {
            --nodes[v].term;
            return true;
        } else {
            return false;
        }
    }

    void sorted(vector<string> &out, int v = 0) const {
        for (int i = 0; i < nodes[v].term; ++i)
            out.push_back(out.back());
        for (int i = 0; i < ALPHABET; ++i) {
            if (nodes[v].next[i]) {
                out.back() += i + FIRST;
                sorted(out, nodes[v].next[i]);
                out.back().pop_back();
            }
        }
    }

    bool max_xor(const string &s, string &out, int v = 0, int ind = 0) {
        if (nodes[v].term)
            return true;
        if (ind == NUMLEN)
            return false;
        int curr = s[ind] - FIRST;
        if (!nodes[v].next[1 - curr]) {
            if (!nodes[v].next[curr])
                return false;
            out += curr + FIRST;
            if (!max_xor(s, out, nodes[v].next[curr], ind + 1)) {
                out.pop_back();
                return false;
            } else {
                return true;
            }
        }
        out += (1 - curr) + FIRST;
        if (!max_xor(s, out, nodes[v].next[1 - curr], ind + 1)) {
            out.pop_back();
            out += curr + FIRST;
            if (!max_xor(s, out, nodes[v].next[curr], ind + 1)) {
                out.pop_back();
                return false;
            } else {
                return true;
            }
        } else {
            return true;
        }
    }
};

int main() {
    fast_io

    Trie trie;
    trie.insert(bitset<NUMLEN>(0).to_string());
    int q;
    cin >> q;
    for (int k = 0; k < q; ++k) {
        char t;
        int x;
        cin >> t >> x;
        if (t == '+') {
            trie.insert(bitset<NUMLEN>(x).to_string());
        } else if (t == '-') {
            trie.erase(bitset<NUMLEN>(x).to_string());
        } else if (t == '?') {
            string ans;
            trie.max_xor(bitset<NUMLEN>(x).to_string(), ans);
            cout << (stoi(ans, nullptr, 2) ^ x) << '\n';
        }
    }
}