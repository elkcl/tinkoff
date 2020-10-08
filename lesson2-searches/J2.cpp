#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <functional>
#include <utility>

using namespace std;
using vi = vector<int>;
using ld = long double;

const ld eps = 1e-9;

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

struct Segment {
    ld l;
    ld r;
    bool isValid = true;
};

bool operator<(Segment a, Segment b) {
    if (a.l == b.l) {
        return a.r - b.r < eps;
    } else {
        return a.l - b.l < eps;
    }
}

Segment operator*(Segment a, Segment b) {
    if (b < a) swap(a, b);
    if (b.l - a.r > eps) {
        return {0, 0, false};
    } else {
        return {b.l, a.r};
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int n;
        cin >> n;
        if (n == 0) break;
        vi x(n);
        vi y(n);
        vi w(n);
        for (int i=0; i<n; ++i) {
            cin >> x[i] >> y[i] >> w[i];
        }
        ld r = realBinarySearch(0, 1e14, [n, &x, &y, &w](ld k) {
            Segment xrange{x[0]-k/w[0], x[0]+k/w[0]};
            Segment yrange{y[0]-k/w[0], y[0]+k/w[0]};
            for (int i=1; i<n; ++i) {
                xrange = xrange * Segment{x[i]-k/w[i], x[i]+k/w[i]};
                yrange = yrange * Segment{y[i]-k/w[i], y[i]+k/w[i]};
                if (!xrange.isValid || !yrange.isValid) return true;
            }
            return false;
        });
        Segment xrange{x[0]-r/w[0], x[0]+r/w[0]};
        Segment yrange{y[0]-r/w[0], y[0]+r/w[0]};
        for (int i=1; i<n; ++i) {
            xrange = xrange * Segment{x[i] - r / w[i], x[i] + r / w[i]};
            yrange = yrange * Segment{y[i] - r / w[i], y[i] + r / w[i]};
        }
        cout.setf(ios::fixed);
        cout.precision(10);
        cout << (xrange.l+xrange.r)/2 << " " << (yrange.l+yrange.r)/2 << "\n";
        cout << r << "\n";
    }
}