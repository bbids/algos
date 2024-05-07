#include <bits/stdc++.h>

std::string binary_search(std::vector<int>& arr, int val) {
    int k=0;
    int n=arr.size();
    for (int b = n / 2; b >= 1; b /= 2) {
        while (k + b < n && arr[k + b] <= val) k += b;
    }

    std::cout << arr[k] << '\n';

    if (arr[k] == val) {
        return "Found!";
    } else {
        return "Not found!";
    }

}

int main() {
    int N, el, val;
    std::cin >> N;
    std::vector<int> vect;

    while (N--) {
        std::cin >> el;
        vect.push_back(el);
    }

    std::cin >> val;

    std::cout << binary_search(vect, val) << '\n';
}