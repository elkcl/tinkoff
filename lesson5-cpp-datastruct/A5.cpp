#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <deque>

using namespace std;
using vi = vector<int>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vi v(n);
    for (int& el : v) {
        cin >> el;
    }
    deque<int> q;
    for (int i = 0; i < k; ++i) {
        while (!q.empty() && v[i] < q.back()) {
            q.pop_back();
        }
        q.push_back(v[i]);
    }
    cout << q.front() << " ";
    for (int i = k; i < n; ++i) {
        if (!q.empty() && v[i-k] == q.front()) {
            q.pop_front();
        }
        while (!q.empty() && v[i] < q.back()) {
            q.pop_back();
        }
        q.push_back(v[i]);
        cout << q.front() << " ";
    }
}