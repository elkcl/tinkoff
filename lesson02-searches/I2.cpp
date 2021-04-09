#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <functional>
#include <cmath>

using namespace std;
using vi = vector<int>;
using ld = long double;

const ld eps = 1e-6;

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

    int vp, vf;
    ld a;
    cin >> vp >> vf >> a;

    ld x = realBinarySearch(0, 1, [vp, vf, a](ld k) {
        return ( sqrt(a*a + (k-eps)*(k-eps) - 2*a + 1)/vp
        + sqrt(a*a + (k-eps)*(k-eps) - 2*(k-eps) + 1)/vf )
        > ( sqrt(a*a + (k+eps)*(k+eps) - 2*a + 1)/vp
            + sqrt(a*a + (k+eps)*(k+eps) - 2*(k+eps) + 1)/vf );
    });
    cout.setf(ios::fixed);
    cout.precision(7);
    cout << x << "\n";
}