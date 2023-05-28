// Insertion Sort Algorithm

#include <iostream>
#include <array>

using namespace std;

void descending_sort(int* arr, int arr_length) {
    
    for (int i=arr_length-2; i>=0; i--) {
        int key = arr[i];

        int j = i + 1;

        while (j<arr_length && arr[j] > key) {
            arr[j-1] = arr[j];
            j += 1;
        }
        arr[j-1] = key;
    }
}

void ascending_sort(int* arr, int arr_length) {
    for (int i=1; i<arr_length; i++) {
        int key = arr[i];
        
        int j = i - 1;

        while (j>=0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j -= 1;
        }
        arr[j+1] = key;
    }
}

int main()
{
    int arr[6] = {31, 41, 59, 26, 41, 58}; // C - array 
    array<int, 6> std_array =  {5, 2, 4, 6, 1, 3}; // cpp standard array (try with any)

    int arr_length = sizeof(arr) / sizeof(arr[0]);

    descending_sort(arr, arr_length);

    int arr2[7] = {7, 6, 5, 4, 3, 2, 1};
    ascending_sort(arr2, sizeof(arr2)/sizeof(arr2[0]));

    // print results
    for (int k=0; k<arr_length; k++) {
        cout << arr[k] << " ";
    }
    cout << endl;
    for (int k=0; k<7; k++) {
        cout << arr2[k] << " ";
    }

    return 0;
}