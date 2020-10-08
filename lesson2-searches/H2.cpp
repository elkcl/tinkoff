#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vi r(n);
    vi b(n);
    int debug_sum = 0;
    for (int i=0; i<n; ++i) {
        cin >> r[i] >> b[i];
        debug_sum += r[i];
    }

    int maxInd = max_element(r.begin(), r.end()) - r.begin();
    int maxVotes = r[maxInd];
    vii cost(n);
    for (int i=0; i<n; ++i) {
        if (b[i] == -1) {
            cost[i] = {i, 1e9};
        } else if (i == maxInd) {
            cost[i] = {i, b[i]};
        } else {
            cost[i] = {i, b[i] + (maxVotes - r[i]) / 2 + 1};
        }
    }
    sort(cost.begin(), cost.end(), [](const ii &a, const ii &b) {
       return a.second < b.second;
    });

    cout << cost[0].second << "\n" << cost[0].first + 1 << "\n";
    int debug_acc = 0;
    for (int i=0; i<n; ++i) {
        if (i == cost[0].first) {
            if (i == maxInd) {
                cout << r[i] << " ";
                debug_acc += r[i];
            } else {
                cout << (maxVotes + r[i]) / 2 + 1 << " ";
                debug_acc += (maxVotes + r[i]) / 2 + 1;
            }
        } else if (i == maxInd) {
            if ((maxVotes + r[cost[0].first]) % 2 == 0) {
                cout << (maxVotes + r[cost[0].first]) / 2 - 1 << " ";
                debug_acc += (maxVotes + r[cost[0].first]) / 2 - 1;
            } else {
                cout << (maxVotes + r[cost[0].first]) / 2 << " ";
                debug_acc += (maxVotes + r[cost[0].first]) / 2;
            }
        } else {
            cout << r[i] << " ";
            debug_acc += r[i];
        }
    }
    assert(debug_acc == debug_sum);
}