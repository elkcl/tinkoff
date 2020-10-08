#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(const string &a, const string &b) {
    auto it1 = a.begin();
    auto it2 = b.begin();
    while (it1 != a.end() && it2 != b.end()) {
        if (*it1 > *it2) {
            return true;
        } else if (*it1 < *it2) {
            return false;
        }
        ++it1;
        ++it2;
    }
    if ((it1 == a.end()) != (it2 == b.end())) {
    	return a+b > b+a;
    } else {
    	return false;
    }
}

int main() {
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);

    vector<string> v;
    string in;
    while (getline(cin, in)) {
        //if (in == "END") break;
        v.push_back(in);
    }
    sort(v.begin(), v.end(), cmp);
    for (auto &s : v) {
        cout << s;
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}