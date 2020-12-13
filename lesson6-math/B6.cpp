#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <tuple>
#include <utility>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;

int mod(int a, int b) {
    return ((a %= b) < 0) ? (a + b) : a;
}

// gcd, x, y
tuple<int, int, int> extgcd(int a, int b) {
    if (b == 0) {
        return {a, 1, 0};
    }
    auto [gcd, x, y] = extgcd(b, mod(a, b));
    return {gcd, y, x - (a / b) * y};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c;
    cin >> a >> b >> c;

    int gcd, x, y, u, v, _;
    if (a >= b) {
        tie(gcd, x, y) = extgcd(a, b);
    } else {
        tie(gcd, y, x) = extgcd(b, a);
    }
    if (c % gcd != 0) {
        cout << "Impossible\n";
    } else {
        if (a >= b) {
            tie(_, u, v) = extgcd(a / gcd, b / gcd);
        } else {
            tie(_, v, u) = extgcd(b / gcd, a / gcd);
        }
        cout << gcd << " " << u * (c / gcd) << " " << v * (c / gcd) << "\n";
    }
}