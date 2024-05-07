#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void print_vector(vector<int>& v) {
    for (const int &el : v) {
        cout << el << ' ';
    }
    cout << '\n';
}

vector<int>::iterator partition(vector<int>& arr, vector<int>::iterator start, vector<int>::iterator end) {
    // lomuto partition scheme (no new vectors)
    // start -> start of subarray
    // end -> end of subarray
    auto pivot = end;
    auto startGreater = start; // later on we are swapping this with pivot
        
    for (auto i = start; i < end; ++i) {
        if (*i < *pivot) {
            swap(*i, *startGreater);
            startGreater++;
        }
    }
    swap(*startGreater, *pivot); // pivot swap with pointer p
    // print_vector(arr);

    return startGreater;
}

void quickSort(vector<int>& arr, vector<int>::iterator start, vector<int>::iterator end) {
    int size = end - start + 1;
    if (size > 1) {
        // return iterator pointing to pivot
        auto p = partition(arr, start, end);

        quickSort(arr, start, p - 1);
        quickSort(arr, p + 1, end);
    }
}


void quickSort(vector<int>& arr) {
    quickSort(arr, arr.begin(), --arr.end()); // important -- here !
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n, el;
    cin >> n;
    vector<int> v;
    
    while (n--) {
        cin >> el;
        v.push_back(el);
    }
    
    // cout << distance(v.begin(), --v.end()) << '\n';

    quickSort(v);
    
    return 0;
}
