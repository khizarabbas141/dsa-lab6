#include <iostream>
using namespace std;

const int MAX = 100;

void inputIDs(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "Enter ID " << i + 1 << ": ";
        cin >> arr[i];
    }
}

int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

void displayResult(int index) {
    if (index == -1)
        cout << "This ID is not registered." << endl;
    else
        cout << "ID found at index " << index << endl;
}

int main() {
    int arr[MAX];
    int n, target;

    cout << "Enter number of students: ";
    cin >> n;

    if (n < 0 || n > MAX) {
        cout << "Invalid number of students." << endl;
        return 0;
    }

    inputIDs(arr, n);

    cout << "Enter ID to search: ";
    cin >> target;

    int index = linearSearch(arr, n, target);
    displayResult(index);

    return 0;
}
