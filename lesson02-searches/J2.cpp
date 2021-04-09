#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>

using namespace std;
using vi = vector<int>;
using ld = long double;

const ld eps = 1e-9;

ld realBinarySearch(ld left, ld right, const function<bool(ld)> &check) {
    for (int i = 0; i < 150; ++i) {
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
    cout.setf(ios::fixed);
    cout.precision(10);

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

        auto f = [n, &x, &y, &w](ld x0, ld y0) -> ld {
            ld ans = 0;
            for (int i=0; i<n; ++i) {
                ans = max(ans,
                          w[i] * sqrt((x[i]-x0)*(x[i]-x0)
                          + (y[i]-y0)*(y[i]-y0) ));
            }
            return ans;
        };
        int xmin = *min_element(x.begin(), x.end());
        int xmax = *max_element(x.begin(), x.end());
        int ymin = *min_element(y.begin(), y.end());
        int ymax = *max_element(y.begin(), y.end());
        //cout << xmin << " " << xmax << " " << ymin << " " << ymax << "\n";
        ld x0 = realBinarySearch(xmin, xmax, [f, ymin, ymax](ld xc) {
            return f(xc-eps, realBinarySearch(ymin, ymax, [xc, f](ld yc) {
                return f(xc-eps, yc-eps) > f(xc-eps, yc+eps);
            }))
            > f(xc+eps, realBinarySearch(ymin, ymax, [xc, f](ld yc) {
               return f(xc+eps, yc-eps) > f(xc+eps, yc+eps);
            }));
        });
        ld y0 = realBinarySearch(ymin, ymax, [x0, f](ld yc) {
            return f(x0, yc-eps) > f(x0, yc+eps);
        });

        cout << x0 << " " << y0 << "\n";
        /**cout << "DEBUG: " << f(x0, y0) << "\n";
        if (n == 2) cout << "CORRECT: " << f(1, 1) << "\n";
        else if (n == 3) cout << "CORRECT: " << f(2.4, 3.6) << "\n";**/
    }
}