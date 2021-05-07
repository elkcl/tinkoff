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

const int ALPHABET = 26;
const char FIRST = 'a';

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
};

int main() {
    fast_io

    string s;
    cin >> s;

    Trie t;
    vi dots(1, 0);
    bool last_dot = true;
    string curr;

    for (char c : s) {
        if (c == '.') {
            ++dots.back();
            last_dot = true;
        } else {
            if (last_dot) {
                dots.emplace_back(0);
                if (!curr.empty()) {
                    t.insert(curr);
                    curr.clear();
                }
            }
            curr += c;
            last_dot = false;
        }
    }
    if (!curr.empty())
        t.insert(curr);

    vector<string> out{""};
    t.sorted(out);
    out.pop_back();
    for (int i = 0; i < out.size(); ++i) {
        while (dots[i]) {
            cout << '.';
            --dots[i];
        }
        cout << out[i];
    }
    while (dots.back()) {
        cout << '.';
        --dots.back();
    }
    cout << '\n';
}