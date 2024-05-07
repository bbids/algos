#include <bits/stdc++.h>

std::vector<int> countingSort(std::vector<int>& arr, int N) {
    int appearanceCount;
    std::vector<int> counter(N);

    for (auto &el : arr) {
        counter[el] += 1;
    }

    std::vector<int> sorted;

    for (int i = 0; i < N; ++i) {
        appearanceCount = counter[i];
        while (appearanceCount--) {
            sorted.push_back(i);
        }
    }

    return sorted;
}

int main() {
    int N, el;
    std::vector<int> v, sorted;
    std::cin >> N;

    for (int i = 0; i < N; ++i) {
        std::cin >> el;
        v.push_back(el);
    }

    sorted = countingSort(v, N);

    for (auto &el : sorted) {
        std::cout << el << ' ';
    }
    std::cout << '\n';
}