#pragma GCC optimize("O3")

#include <iostream>
#include <numeric>

using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int x = a * d + b * c;
    int y = b * d;
    int g = gcd(x, y);
    cout << x / g << " " << y / g << "\n";
}