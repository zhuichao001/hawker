// To find whether an array is subset of another array

#include <bits/stdc++.h>
using namespace std;

/* Function prototypes */
void quickSort(int* arr, int si, int ei);
int binarySearch(int arr[], int low, int high, int x);

/* Return 1 if arr2[] is a subset of arr1[] */
bool isSubset(int arr1[], int arr2[], int m, int n) {
    if (m<n) {
        return isSubset(arr2, arr1, n, m);
    }
    int i = 0;

    quickSort(arr1, 0, m - 1);
    for (i = 0; i < n; i++) {
        if (binarySearch(arr1, 0, m - 1, arr2[i]) == -1)
            return 0;
    }

    /* If we reach here then all elements of arr2[] are present in arr1[] */
    return 1;
}

int binarySearch(int arr[], int low, int high, int x) {
    if (high >= low) {
        int mid = (low + high) / 2;

        /* Check if arr[mid] is the first
           occurrence of x. arr[mid] is first
           occurrence if x is one of the following
           is true:
           (i) mid == 0 and arr[mid] == x
           (ii) arr[mid-1] < x and arr[mid] == x    */
        if ((mid == 0 || x > arr[mid - 1])
                && (arr[mid] == x))
            return mid;
        else if (x > arr[mid])
            return binarySearch(arr, (mid + 1), high, x);
        else
            return binarySearch(arr, low, (mid - 1), x);
    }
    return -1;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int A[], int si, int ei) {
    int x = A[ei];
    int i = (si - 1);
    for (int j = si; j <= ei - 1; ++j) {
        if (A[j] <= x) {
            ++i;
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i + 1], &A[ei]);
    return (i + 1);
}

void quickSort(int A[], int si, int ei) {
    if (si < ei) {
        int pi = partition(A, si, ei);
        quickSort(A, si, pi - 1);
        quickSort(A, pi + 1, ei);
    }
}

int main() {
    int arr1[] = { 11, 1, 13, 21, 3, 7 };
    int arr2[] = { 11, 3, 7, 1 };

    int m = sizeof(arr1) / sizeof(arr1[0]);
    int n = sizeof(arr2) / sizeof(arr2[0]);

    if (isSubset(arr1, arr2, m, n))
        cout << "arr2[] is subset of arr1[] ";
    else
        cout << "arr2[] is not a subset of arr1[] ";

    return 0;
}
