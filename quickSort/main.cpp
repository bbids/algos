#include <bits/stdc++.h>

using namespace std;

vector<int> partition(const vector<int> &arr) 
{
    
    vector<int> left, right, equal;
    int pivot = arr[0];
    
    // partition
    for (const int& el : arr) {
        if (el < pivot) left.push_back(el);
        else if (el > pivot) right.push_back(el);
        else equal.push_back(el);
    }
    
    // continue recursion
    if (left.size() > 1) left = partition(left);
    if (right.size() > 1) right = partition(right);
    
    // merge
    left.insert(left.end(), equal.begin(), equal.end());
    left.insert(left.end(), right.begin(), right.end());
    
    return left;
}

void quickSort(vector <int> &arr) {
    arr = partition(arr);
}

int main() {
    vector<int> v = {5, 1, 2, 9, -124, 42, 24};

    quickSort(v);

    for (const int &el : v) {
        cout << el  << ' ';
    }
    cout << '\n';

    return 0;
}