#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <tuple>
#include <utility>
#include <type_traits>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;

template<typename T>
T mod(T a, T b) {
    static_assert(is_integral<T>::value, "not an integral type");
    return ((a %= b) < 0) ? (a + b) : a;
}

// gcd, x, y
template<typename T>
tuple<T, T, T> extgcd(T a, T b) {
    static_assert(is_integral<T>::value, "not an integral type");
    bool gr = a >= b;
    if (!gr) swap(a, b);
    if (b == 0) {
        return {a, 1, 0};
    }
    auto [gcd, x, y] = extgcd(b, mod(a, b));
    if (gr) {
        return {gcd, y, x - (a / b) * y};
    } else {
        return {gcd, x - (a / b) * y, y};
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll a, m;
    cin >> a >> m;
    auto [gcd, x, y] = extgcd(a, m);
    if (gcd != 1) {
        cout << "-1\n";
    } else {
        cout << mod(x, m) << "\n";
    }
}