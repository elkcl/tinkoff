#pragma GCC optimize("O3")
//#pragma GCC target("avx2")

#include <iostream>
#include <random>
#include <vector>
#include <utility>
#include <string>

using namespace std;
typedef uint32_t ui;

struct Letter {
    int num;
    ui c;
};

bool operator<(Letter a, Letter b) {
    return a.c > b.c;
}

bool operator>(Letter a, Letter b) {
    return a.c < b.c;
}

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
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);
    freopen("aurora.in", "r", stdin);
    freopen("aurora.out", "w", stdout);
    rng.seed(time(nullptr));

    string s;
    cin >> s;
    vector<Letter> weights(26);
    for (int i=0; i < 26; ++i) {
        ui w;
        cin >> w;
        weights[i] = Letter{i, w};
    }
    quicksort(weights, 0, 25);
    vector<int> letterCount(26, 0);
    for (char ch : s) {
        ++letterCount[ch - 'a'];
    }
    int p = 0;
    for (int i=0; i<26; ++i) {
        int letterNum = weights[i].num;
        if (letterCount[letterNum] >= 2) {
            letterCount[letterNum] -= 2;
            s[p] = s[s.size()-1 - p] = 'a' + letterNum;
            ++p;
        }
    }
    for (int i=0; i<26; ++i) {
        for (int j=0; j<letterCount[i]; ++j) {
            s[p] = 'a' + i;
            ++p;
        }
    }
    cout << s;

    fclose(stdin);
    fclose(stdout);
    return 0;
}