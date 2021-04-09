#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,sse,sse2,sse3,ssse3,sse4.1,sse4.2")

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <unordered_map>

using namespace std;
using ll = long long;
using si = set<int>;
using sll = set<ll>;
using vsll = unordered_map<int, sll>;
using umllsi = unordered_map<ll, si>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    int m, k;
    cin >> n >> m >> k;
    vsll sets;
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
                for (auto &el : sets[s]) {
                    setsOfNum[el].erase(s);
                }
                sets[s].clear();
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