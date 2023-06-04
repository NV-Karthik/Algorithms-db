#include <iostream>
#include <array>

using namespace std;

// void selection_sort(array arr, int n)


int main()
{
    array <int, 6> arr = {6, 5, 4, 3, 2, 1};
    int n = arr.size();
    array <int, arr.size()> sorted_arr = {0}; // array which has the sorted entries
    
    // select the smallest entry and swap with the least index
    for (int i=0; i<n-1; i++) {
        int least_val = arr.at(i);
        int least_index = i;
        for (int j=i+1; j<n; j++) {
            if (arr.at(j) < arr.at(least_index)) {
                least_index = j;
            }
        }
        arr.at(i) = arr.at(least_index);
        arr.at(least_index) = least_val;
    } 


    // print results
    for (int k=0; k<n; k++) {
        cout << arr.at(k) << " ";
    }

    return 0;
}