#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int> &v, int low, int high) {
    int pivot = v[low];
    int left = low;
    int right = high;
    while (left < right) {

        while (v[left] <= pivot && left < high) {
            left++;
        }
        while (v[right] > pivot) {
            right--;
        }
        if (left < right) {
            swap(v[left], v[right]);
        }
    }
    swap(v[low], v[right]);
    return right;
}

void quickSort(vector<int> &v, int low, int high) {
    if (low < high) {
        int pi = partition(v, low, high);
        quickSort(v, low, pi - 1);
        quickSort(v, pi + 1, high);
    }
}

int main() {
    vector<int> data = {25, 30, 12, 17, 26, 8};
    quickSort(data, 0, data.size() - 1);
    for (int n : data)
        cout << n << " ";
    return 0;
}
