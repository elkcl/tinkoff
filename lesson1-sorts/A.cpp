#pragma GCC optimize("O3")
//#pragma GCC target("avx2")

#include <iostream>
#include <random>
#include <vector>
#include <utility>

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

struct Pair {
        int l;
        int r;
    };

bool operator<(Pair& a, Pair& b) {
    if (a.r > b.r) {
        return true;
    } else if (a.r == b.r) {
        return a.l < b.l;
    } else {
        return false;
    }
}

bool operator>(Pair& a, Pair& b) {
    if (a.r < b.r) {
        return true;
    } else if (a.r == b.r) {
        return a.l > b.l;
    } else {
        return false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    rng.seed(time(nullptr));

    int n;
    cin >> n;
    vector<Pair> v(n);
    for (int i=0; i<n; ++i) {
        cin >> v[i].l >> v[i].r;
    }

    quicksort(v, 0, n-1);

    for (int i=0; i<n; ++i) {
        cout << v[i].l << " " << v[i].r << "\n";
    }
}