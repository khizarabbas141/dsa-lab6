#include <iostream>
using namespace std;

const int MAX = 100;

void inputSortedIDs(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "Enter registration number " << i + 1 << ": ";
        cin >> arr[i];
    }
}
bool isSorted(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1])
            return false;
    }
    return true;
}

int binarySearch(int arr[], int low, int high, int target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int main() {
    int arr[MAX];
    int n, target;

    cout << "Enter number of registration numbers: ";
    cin >> n;

    if (n < 0 || n > MAX) {
        cout << "Invalid size." << endl;
        return 0;
    }

    inputSortedIDs(arr, n);


    if (!isSorted(arr, n)) {
        cout << "The array is not sorted, binary search cannot be used." << endl;
        return 0;
    }

    cout << "Enter registration number to search: ";
    cin >> target;

    
    int pos = binarySearch(arr, 0, n - 1, target);

    if (pos == -1)
        cout << "Not found" << endl;
    else
        cout << "Found at index " << pos << endl;

    return 0;
}
