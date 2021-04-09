#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <functional>

using namespace std;
using vi = vector<int>;
using ld = long double;

ld realBinarySearch(ld left, ld right, const function<bool(ld)> &check) {
    if (check(right)) swap(left, right);
    for (int i = 0; i < 200; ++i) {
        ld middle = (left + right) / 2;
        if (check(middle)) {
            left = middle;
        } else {
            right = middle;
        }
    }
    return right;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c, d;
    cin >> a >> b >> c >> d;
    ld x = realBinarySearch(-1e10, 1e10, [a, b, c, d](ld k) {
        return a*k*k*k + b*k*k + c*k + d < 0;
    });
    cout.setf(ios::fixed);
    cout.precision(4);
    cout << x << "\n";
}