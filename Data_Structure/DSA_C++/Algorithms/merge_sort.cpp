#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int> &v, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);

    int i;
    for (i = 0; i < n1; i++)
        L[i] = v[left + i];
    for (i = 0; i < n2; i++)
        R[i] = v[mid + 1 + i];

    i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            v[k] = L[i++];
        } else {
            v[k] = R[j++];
        }
        k++;
    }
    while (i < n1)
        v[k++] = L[i++];
    while (j < n2)
        v[k++] = R[j++];
}

void mergeSort(vector<int> &v, int left, int right) {
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSort(v, left, mid);
    mergeSort(v, mid + 1, right);
    merge(v, left, mid, right);
}

int main() {
    vector<int> data = {12, 11, 13, 5, 6, 7};
    mergeSort(data, 0, data.size() - 1);
    for (int n : data)
        cout << n << " ";
    return 0;
}
