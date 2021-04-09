#pragma GCC optimize("O3")

#include <iostream>
#include <deque>

using namespace std;
using qi = deque<int>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    qi q1;
    qi q2;
    bool even = true;
    for (int _q = 0; _q < n; ++_q) {
        char queryType;
        cin >> queryType;
        if (queryType == '+') {
            int x;
            cin >> x;
            q2.push_back(x);
            if (even) {
                q1.push_back(q2.front());
                q2.pop_front();
            }
            even = !even;
        } else if (queryType =='*') {
            int x;
            cin >> x;
            if (even) {
                q1.push_back(x);
                even = false;
            } else {
                q2.push_front(x);
                even = true;
            }
        } else if (queryType == '-') {
            cout << q1.front() << "\n";
            q1.pop_front();
            if (even) {
                q1.push_back(q2.front());
                q2.pop_front();
            }
            even = !even;
        }
    }
}