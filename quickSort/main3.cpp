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

void partition(vector<int> &arr,int start, int end) {
    // lomuto partition scheme (no new vectors)
    // lp -> start of subarry
    // gp -> end of subarray
    int size = end - start + 1;
    if (size > 1) {
        int pivot = arr[end]; // last element of subarray
        int p=start; // point to start of greater (than pivot) subarry
        
        for (int i = start; i < end; ++i) {
            if (arr[i] < pivot) {
                swap(arr[i], arr[p]);
                p++;
            }
        }
        swap(arr[p], arr[end]); // pivot swap with pointer p
        
        // print_vector(arr);
        
        partition(arr, start, p - 1);
        partition(arr, p + 1, end);
    }
}


void quickSort(vector<int> &arr) {
    int N = arr.size();
    
    partition(arr, 0, N - 1);
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
    
    quickSort(v);

    print_vector(v);
    
    return 0;
}
