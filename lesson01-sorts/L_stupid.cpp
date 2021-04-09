#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int factorial(int n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

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
    return it1 == a.end() && it2 != b.end();
}

int main() {
    //freopen("number.in", "r", stdin);
    //freopen("number.out", "w", stdout);

    vector<string> v;
    string in;
    while (getline(cin, in)) {
        if (in == "END") break;
        v.push_back(in);
    }
    int n = v.size();
    string num;
    for (int i=0; i<factorial(n); ++i) {
        string st;
        for (auto &s : v) {
            st += s;
        }
        num = max(num, st);
        next_permutation(v.begin(), v.end());
    }
    cout << num;

    //fclose(stdin);
    //fclose(stdout);
    return 0;
}