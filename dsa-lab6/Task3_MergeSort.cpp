#include <iostream>
using namespace std;

const int MAX = 100;

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[MAX], R[MAX];

    for (int a = 0; a < n1; a++)
        L[a] = arr[left + a];
    for (int b = 0; b < n2; b++)
        R[b] = arr[mid + 1 + b];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void displayArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int marks[MAX];
    int n;

    cout << "Enter number of students: ";
    cin >> n;

    if (n < 0 || n > MAX) {
        cout << "Invalid size." << endl;
        return 0;
    }

    for (int i = 0; i < n; i++) {
        cout << "Enter marks " << i + 1 << ": ";
        cin >> marks[i];
    }

    cout << "Before sorting: ";
    displayArray(marks, n);

    mergeSort(marks, 0, n - 1);

    cout << "After sorting:  ";
    displayArray(marks, n);

    return 0;
}
