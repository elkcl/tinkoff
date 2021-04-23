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

struct BigInt {
    vi num;
    bool positive;
    int len;

    BigInt() {
        positive = true;
        len = 0;
    }
    BigInt(vi s, bool b): num{move(s)}, positive{b}, len{static_cast<int>(num.size())} {}
    BigInt(string& source) {
        positive = true;
        if (source[0] == '-') {
            source.erase(0, 1);
            positive = false;
        }
        for (int i = source.size()-1; i >= 0; --i) {
            num.push_back(source[i] - '0');
        }
        len = num.size();
    }

    BigInt abs() const {
        return BigInt{num, true};
    }
    BigInt operator-() const {
        return BigInt{num, !positive};
    }
    BigInt operator<<(int n) const {
        BigInt ans{num, positive};
        ans.num.insert(ans.num.begin(), n, 0);
        ans.len = ans.num.size();
        return ans;
    }
    string str() const {
        string ans;
        if (!positive) ans += '-';
        int i = len - 1;
        while (num[i] == 0 && i > 0) --i;
        for (; i >= 0; --i) {
            ans += '0' + num[i];
        }
        return ans;
    }
};

BigInt operator+(const BigInt& a, const BigInt& b);
BigInt operator-(const BigInt& a, const BigInt& b);
BigInt operator*(const BigInt& a, const BigInt& b);
BigInt mulrec(const BigInt& a, const BigInt& b);

BigInt operator+(const BigInt& a, const BigInt& b) {
    if (a.positive && !b.positive) return a - b.abs();
    if (!a.positive && b.positive) return b - a.abs();
    if (!a.positive && !b.positive) return -(a.abs() + b.abs());

    BigInt ans;
    ans.num.reserve(max(a.len, b.len) + 1);
    int carry = 0;

    if (a.len >= b.len) {
        for (int i = 0; i < b.len; ++i) {
            ans.num.push_back((a.num[i] + b.num[i] + carry) % 10);
            carry = (a.num[i] + b.num[i] + carry) / 10;
            ++ans.len;
        }
        for (int i = b.len; i < a.len; ++i) {
            ans.num.push_back((a.num[i] + carry) % 10);
            carry = (a.num[i] + carry) / 10;
            ++ans.len;
        }
    } else {
        for (int i = 0; i < a.len; ++i) {
            ans.num.push_back((a.num[i] + b.num[i] + carry) % 10);
            carry = (a.num[i] + b.num[i] + carry) / 10;
            ++ans.len;
        }
        for (int i = a.len; i < b.len; ++i) {
            ans.num.push_back((b.num[i] + carry) % 10);
            carry = (b.num[i] + carry) / 10;
            ++ans.len;
        }
    }

    if (carry != 0) {
        ans.num.push_back(carry);
        ++ans.len;
    }
    return ans;
}

BigInt operator-(const BigInt& a, const BigInt& b) {
    if (a.positive && !b.positive) return a + b.abs();
    if (!a.positive && b.positive) return -(a.abs() + b.abs());
    if (!a.positive && !b.positive) return b - a.abs();

    BigInt ans;
    ans.num.reserve(max(a.len, b.len) + 1);
    int borrow = 0;

    for (int i = 0; i < b.len; ++i) {
        if (a.num[i] - borrow < b.num[i]) {
            ans.num.push_back(10 + a.num[i] - b.num[i] - borrow);
            borrow = 1;
            ++ans.len;
        } else {
            ans.num.push_back(a.num[i] - b.num[i] - borrow);
            borrow = 0;
            ++ans.len;
        }
    }
    for (int i = b.len; i < a.len; ++i) {
        if (a.num[i] - borrow < 0) {
            ans.num.push_back(10 + a.num[i] - borrow);
            borrow = 1;
            ++ans.len;
        } else {
            ans.num.push_back(a.num[i] - borrow);
            borrow = 0;
            ++ans.len;
        }
    }

    return ans;
}

BigInt operator*(const BigInt& a, const BigInt& b) {
    return BigInt{mulrec(a.abs(), b.abs()).num, a.positive == b.positive};
}

BigInt mulrec(const BigInt& ai, const BigInt& bi) {
    if (ai.len == 0 || bi.len == 0) {
        return BigInt{{0}, true};
    }
    if (ai.num.size() == 1 && bi.num.size() == 1) {
        BigInt ans;
        int res = ai.num[0] * bi.num[0];
        ans.num.push_back(res % 10);
        ++ans.len;
        if (res >= 10) {
            ans.num.push_back(res / 10);
            ++ans.len;
        }
        return ans;
    }

    BigInt a{ai.num, ai.positive};
    BigInt b{bi.num, bi.positive};

    if (a.len < b.len) {
        while (*(b.num.end() - 1) == 0 && a.len < b.len) {
            b.num.pop_back();
            --b.len;
        }
        a.num.insert(a.num.end(), b.len - a.len, 0);
        a.len = a.num.size();
        b.len = b.num.size();
    } else if (a.len > b.len) {
        while (*(a.num.end() - 1) == 0 && a.len > b.len) {
            a.num.pop_back();
            --a.len;
        }
        b.num.insert(b.num.end(), a.len - b.len, 0);
        a.len = a.num.size();
        b.len = b.num.size();
    }
    if (!a.num.empty() && !b.num.empty()) {
        while (*(a.num.end() - 1) == 0 && *(b.num.end() - 1) == 0) {
            a.num.pop_back();
            --a.len;
            b.num.pop_back();
            --b.len;
        }
    }
    if (a.len % 2 != 0) {
        a.num.push_back(0);
        ++a.len;
        b.num.push_back(0);
        ++b.len;
    }
    int k = a.len / 2;

    BigInt a1{vi(a.num.begin(), a.num.begin() + k), true};
    BigInt a2{vi(a.num.begin() + k + 1, a.num.end()), true};
    BigInt b1{vi(b.num.begin(), b.num.begin() + k), true};
    BigInt b2{vi(b.num.begin() + k + 1, b.num.end()), true};

    auto p1 = mulrec(a1, b1);
    auto p2 = mulrec(a2, b2);
    auto t = mulrec(a1 + a2, b1 + b2);

    return p1 + ((t - p1 - p2) << k) + (p2 << (2*k));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
//    freopen("multiply.in", "r", stdin);
//    freopen("multiply.out", "w", stdout);

    string n, m;
    cin >> n >> m;
    cout << (BigInt(n) * BigInt(m)).abs().str() << '\n';
}