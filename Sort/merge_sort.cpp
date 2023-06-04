#include <iostream>

using namespace std;

/* function to merge two sub arrays divided in merge sort algorithm. 
    merges arrays {A[p],...A[q]} and {A[q+1], .... A[r]} to form {A[p], ..., A[q], A[q+1], ... ... , A[r]}
    A - total array which is obtained after merging
    p - start index of 1st sub array
    q - end index of 1st sub array
    r - end index of 2nd sub array

    Merge happens such that merged array is always sorted
*/
void merge (int* A, int p, int q, int r) {
    int n1 = q - p + 1; // number of entries in left array
    int n2 = r - q; // r - (q + 1) + 1 // number of entries in right array
    int i = 0;
    int j = 0;

    int* left = (int*) calloc(n1, sizeof(int));
    int* right = (int*) calloc(n2, sizeof(int));

    for (i=0; i<n1; i++){
        left[i] = A[p+i];
    }

    for (j=0; j<n2; j++) {
        right[j] = A[q+j+1];
    }

    i = 0;
    j = 0;

    for (int k=p; k<r+1; k++) {
        if ( (left[i] <= right[j]) && (i<n1) ){
            A[k] = left[i];
            i++;
        }

        else if (j < n2) {
            A[k] = right[j];
            j++;
        }

        else {
            A[k] = left[i];
            i++;
        }
    }

    free(left);
    free(right);
}

// p and r are the starting and ending indices of array to be sorted
void merge_sort(int* A, int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        merge_sort(A, p, q);
        merge_sort(A, q+1, r);
        merge(A, p, q, r);
    }

    else {
        merge(A, 0, 0, 0);
    }
}


int main()
{
    int arr[6] = {6, 5, 4, 3, 2, 1};
    int arr_length = sizeof(arr) / sizeof(arr[0]);

    merge_sort(arr, 0, 5);

    // print results
    for (int k=0; k<arr_length; k++) {
        cout << arr[k] << " ";
    }
    return 0;
}