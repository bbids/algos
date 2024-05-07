#include <bits/stdc++.h>

using namespace std;

void insertion_sort(vector<int> &arr) {
    int el, i, j;
    for (i = 1; i < arr.size(); ++i) {
        el = arr[i];
        for (j = i - 1; j >= 0 && el < arr[j]; --j) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = el;
    }
}


int main() {
    int n, el;
    cin >> n;
    vector<int> v;

    while (n--) {
        cin >> el;
        v.push_back(el);
    }

    insertion_sort(v);

    for (const auto &el : v) {
        cout << el << ' ';
    }
    cout << '\n';


    return 0;
}