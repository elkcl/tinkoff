#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <functional>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;

int binarySearch(int lo, int hi, const function<bool(int)> &check) {
    int left = lo-1;
    int right = hi+1;
    while (right - left > 1) {
        int middle = (left + right) / 2;
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

    int n, m, l;
    cin >> n >> m >> l;
    vvi A(n, vi(l));
    vvi B(m, vi(l));
    for (int i=0; i<n; ++i) {
        for (int j=0; j<l; ++j) {
            cin >> A[i][j];
        }
    }
    for (int i=0; i<m; ++i) {
        for (int j=0; j<l; ++j) {
            cin >> B[i][j];
        }
    }
    int q;
    cin >> q;
    for (int c1=0; c1<q; ++c1) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        int index = binarySearch(0, l-1, [&A, &B, a, b](int k) {
            return A[a][k] < B[b][k];
        });
        if (index == l) {
            cout << l << "\n";
        } else if (index == 0) {
            cout << 1 << "\n";
        } else if (A[a][index] == B[b][index] || A[a][index] < B[b][index-1]) {
            cout << index+1 << "\n";
        } else {
            cout << index << "\n";
        }
    }
}