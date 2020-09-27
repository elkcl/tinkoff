#pragma GCC optimize("O3")
//#pragma GCC target("avx2")

#include <iostream>
#include <random>
#include <vector>
#include <utility>
#include <string>

using namespace std;

mt19937 rng;

template <typename T>
int partition(vector<T> &arr, int l, int r) {
    uniform_int_distribution<int> gen(l, r-1);
    int ind = gen(rng);
    T mid = arr[ind];
    int i = l-1;
    int j = r+1;
    while (true) {
        do {
            ++i;
        } while (arr[i] < mid);
        do {
            --j;
        } while (arr[j] > mid);
        if (i >= j) return j;
        swap(arr[i], arr[j]);
    }
}

template <typename T>
void quicksort(vector<T> &arr, int l, int r) {
    if (l >= r) return;
    int p = partition(arr, l, r);
    quicksort(arr, l, p);
    quicksort(arr, p+1, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    rng.seed(time(nullptr));

    string a, b;
    cin >> a >> b;
    vector<char> v1(a.begin(), a.end());
    vector<char> v2(b.begin(), b.end());
    quicksort(v1, 0, v1.size()-1);
    quicksort(v2, 0, v2.size()-1);
    if (v1 == v2) cout << "YES" << "\n";
    else cout << "NO" << "\n";
}