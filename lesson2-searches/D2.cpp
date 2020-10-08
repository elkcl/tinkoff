#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <functional>
#include <cmath>

using namespace std;
using vi = vector<int>;
using ld = long double;

 ld realBinarySearch(ld left, ld right, const function<bool(ld)> &check) {
    for (int i = 0; i < 100; ++i) {
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

    ld C;
    cin >> C;
    ld x = realBinarySearch(0.0, C, [C](ld k) {
        return (k*k + sqrt(k)) < C;
    });
    cout.setf(ios::fixed);
    cout.precision(7);
    cout << x << "\n";
}