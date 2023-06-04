// linear search algorithm

#include <iostream>

using namespace std;

// Returns the index of the element to be found, returns -1 if not found 
int linear_search(int* arr, int arr_length, int key) {
    for (int i=0; i<arr_length; i++) {
        if (arr[i] == key) {
            return i;
        }
    }

    return -1;
}

int main()
{
    int arr[5] = {55, 4, 77, 1, 215};
    int key = 75; // element to be searched for

    cout << linear_search(arr, sizeof(arr)/sizeof(arr[0]), key) << endl;

    return 0;
}