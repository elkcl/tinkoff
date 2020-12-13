#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <unordered_map>

using namespace std;
using ll = long long;
using si = set<int>;
using sll = set<ll>;
using vsll = vector<sll>;
using umllsi = unordered_map<ll, si>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    int m, k;
    cin >> n >> m >> k;
    vsll sets(m+1);
    umllsi setsOfNum;
    for (int q = 0; q < k; ++q) {
        string queryType;
        cin >> queryType;
        if (queryType == "ADD") {
            int s;
            ll e;
            cin >> e >> s;
            sets[s].insert(e);
            setsOfNum[e].insert(s);
        } else if (queryType == "DELETE") {
            int s;
            ll e;
            cin >> e >> s;
            sets[s].erase(e);
            setsOfNum[e].erase(s);
        } else if (queryType == "CLEAR") {
            int s;
            cin >> s;
            if (!sets[s].empty()) {
                sets[s].clear();
                for (auto &el : setsOfNum) {
                    el.second.erase(s);
                }
            }
        } else if (queryType == "LISTSET") {
            int s;
            cin >> s;
            if (sets[s].empty()) {
                cout << "-1\n";
            } else {
                for (auto el : sets[s]) {
                    cout << el << " ";
                }
                cout << "\n";
            }
        } else if (queryType == "LISTSETSOF") {
            ll e;
            cin >> e;
            if (setsOfNum[e].empty()) {
                cout << "-1\n";
            } else {
                for (auto el : setsOfNum[e]) {
                    cout << el << " ";
                }
                cout << "\n";
            }
        }
    }
}