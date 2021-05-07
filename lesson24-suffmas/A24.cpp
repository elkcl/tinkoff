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
    cin >> s;
    s += '$';
    const int ALPHABET = 26 + 1;

    vi char_count(ALPHABET + 1, 0);
    for (char ch : s) {
        ++char_count[((ch == '$') ? 0 : ch - 'a' + 1) + 1];
    }
    for (int i = 2; i < ALPHABET; ++i) {
        char_count[i] += char_count[i - 1];
    }
    vi suffs(s.size());
    for (int i = 0; i < s.size(); ++i) {
        suffs[char_count[(s[i] == '$') ? 0 : s[i] - 'a' + 1]++] = i;
    }

    vi classes(s.size());
    int class_count = 0;
    char last = '$';
    for (int el : suffs) {
        if (s[el] != last) {
            last = s[el];
            ++class_count;
        }
        classes[el] = class_count;
    }

    for (int curr = 1; curr / 2 <= s.size(); curr *= 2) {
        vi swapped(s.size());
        for (int rank = 0; rank < suffs.size(); ++rank) {
            swapped[rank] = (suffs[rank] - curr + 2 * s.size()) % s.size();
        }
        vi count(s.size() + 1, 0);
        for (int el : swapped) {
            ++count[classes[el] + 1];
        }
        for (int i = 2; i < s.size(); ++i) {
            count[i] += count[i - 1];
        }
        for (int el : swapped) {
            suffs[count[classes[el]]++] = el;
        }

        vi classes_new(s.size());
        class_count = 0;
        classes_new[0] = 0;
        for (int rank = 1; rank < suffs.size(); ++rank) {
            int right_suff_curr = (suffs[rank] + curr) % s.size();
            int right_suff_prev = (suffs[rank - 1] + curr) % s.size();
            if (classes[suffs[rank - 1]] != classes[suffs[rank]] || classes[right_suff_prev] != classes[right_suff_curr]) {
                ++class_count;
            }
            classes_new[suffs[rank]] = class_count;
        }
        classes = classes_new;
    }

    for (int i = 1; i < suffs.size(); ++i) {
        cout << suffs[i] + 1 << ' ';
    }
    cout << '\n';
}