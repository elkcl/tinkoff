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

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#define file_io(x) freopen((x) + ".in", "r", stdin); freopen((x) + ".out", "w", stdout);

int main() {
    fast_io

    string s;
    ll k;
    cin >> s >> k;
    --k;
    //if (k > static_cast<int>(1e5) + 1) k = static_cast<int>(1e5) + 1;
    const char SYMB = '$';
    const char FIRST = 'a';
    s += SYMB;
    const int ALPHABET = 26 + 1;
    int n = s.size();

    vi char_count(ALPHABET + 1, 0);
    for (char ch : s) {
        ++char_count[((ch == SYMB) ? 0 : ch - FIRST + 1) + 1];
    }
    for (int i = 2; i < ALPHABET; ++i) {
        char_count[i] += char_count[i - 1];
    }
    vi suffs(n);
    for (int i = 0; i < n; ++i) {
        suffs[char_count[(s[i] == SYMB) ? 0 : s[i] - FIRST + 1]++] = i;
    }

    vi classes(n);
    int class_count = 0;
    char last = s[suffs[0]];
    for (int el : suffs) {
        if (s[el] != last) {
            last = s[el];
            ++class_count;
        }
        classes[el] = class_count;
    }

    for (int curr = 1; curr / 2 <= n; curr *= 2) {
        vi swapped(n);
        for (int rank = 0; rank < suffs.size(); ++rank) {
            swapped[rank] = (suffs[rank] - curr + 2 * n) % n;
        }
        vi count(n + 1, 0);
        for (int el : swapped) {
            ++count[classes[el] + 1];
        }
        for (int i = 2; i < n; ++i) {
            count[i] += count[i - 1];
        }
        for (int el : swapped) {
            suffs[count[classes[el]]++] = el;
        }

        vi classes_new(n);
        class_count = 0;
        classes_new[0] = 0;
        for (int rank = 1; rank < suffs.size(); ++rank) {
            int right_suff_curr = (suffs[rank] + curr) % n;
            int right_suff_prev = (suffs[rank - 1] + curr) % n;
            if (classes[suffs[rank - 1]] != classes[suffs[rank]] || classes[right_suff_prev] != classes[right_suff_curr]) {
                ++class_count;
            }
            classes_new[suffs[rank]] = class_count;
        }
        classes = classes_new;
    }

    vi ranks(n);
    for (int i = 0; i < n; ++i) {
        ranks[suffs[i]] = i;
    }
    vi lcp(n-1);

    int last_lcp = 0;
    for (int i = 0; i < n; ++i) {
        if (last_lcp > 0)
            --last_lcp;
        if (ranks[i] == n - 1) {
            last_lcp = 0;
            continue;
        }
        int j = suffs[ranks[i] + 1];
        while (max(i + last_lcp, j + last_lcp) < n && s[i + last_lcp] == s[j + last_lcp])
            ++last_lcp;
        lcp[ranks[i]] = last_lcp;
    }

    vll substrs(n+1);
    substrs[0] = 0;
    substrs[1] = n - suffs[0] - 1;
    for (ll i = 1; i < n; ++i) {
        substrs[i + 1] = n - suffs[i] - lcp[i - 1] - 1;
    }
    for (ll i = 2; i < n+1; ++i) {
        substrs[i] += substrs[i - 1];
    }
    auto it = upper_bound(substrs.begin(), substrs.end() - 1, k) - 1;
    ll count = k + lcp[it - substrs.begin() - 1] + 1 - *it;
    cout << s.substr(suffs[it - substrs.begin()], min(count, static_cast<long long>(n - suffs[it - substrs.begin()] - 1))) << '\n';
}