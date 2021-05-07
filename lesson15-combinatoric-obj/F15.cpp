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
#include <stack>

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
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);

void gen(int n, vc& seq, stack<char>& bal, int ind = 0) {
    if (ind == n * 2) {
        for (char el : seq)
            cout << el;
        cout << '\n';
        return;
    }

    if (bal.size() == n * 2 - ind) {
        if (bal.top() == '(') {
            seq[ind] = ')';
            bal.pop();
            gen(n, seq, bal, ind + 1);
            bal.push('(');
        } else {
            seq[ind] = ']';
            bal.pop();
            gen(n, seq, bal, ind + 1);
            bal.push('[');
        }
        return;
    }

    seq[ind] = '(';
    bal.push('(');
    gen(n, seq, bal, ind + 1);
    bal.pop();

    seq[ind] = '[';
    bal.push('[');
    gen(n, seq, bal, ind + 1);
    bal.pop();

    if (!bal.empty()) {
        if (bal.top() == '(') {
            seq[ind] = ')';
            bal.pop();
            gen(n, seq, bal, ind + 1);
            bal.push('(');
        } else {
            seq[ind] = ']';
            bal.pop();
            gen(n, seq, bal, ind + 1);
            bal.push('[');
        }
    }
}

int main() {
    fast_io
    //file_io("brackets2")

    int n;
    cin >> n;
    if (n == 0 || n % 2 == 1)
        return 0;

    vc seq(n);
    stack<char> bal;
    gen(n / 2, seq, bal);
}