/*
Creation of an abstract datatype similar to an array and implementing some useful methods for it
*/

#include <stdio.h>
#include <stdlib.h>

struct myArray
{
    int total_size;
    int used_size;
    int *ptr;
};

// constructor - gives new 'MyArray' object with no elements, used_size will be set to 0
void constructMyArray(struct myArray *arr, int t_size) {
    // (*arr).total_size = t_size;
    // (*arr).used_size = u_size;
    // (*arr).ptr = (int*) malloc(t_size * sizeof(int));

    // same as the above commented block
    arr->total_size = t_size;
    arr->used_size = 0;
    arr->ptr = (int*) malloc(t_size * sizeof(int));
}

// destructor
void destructMyArray(struct myArray *arr) {
    free(arr->ptr);
}

// initializer
void initializeMyArray(struct myArray *arr) {
    printf("Array size is %d.\nEnter num of elements to add to array:", arr->total_size);
    scanf("%d", &(arr->used_size));
    int n;
    for(int i=0; i<arr->used_size; i++) {
        scanf("%d", &n);
        (arr->ptr)[i] = n;
    }
}

// display array elements
void displayMyArray(struct myArray *arr) {
    printf("%d out of %d elements used\n", arr->used_size, arr->total_size);
    for(int i=0; i<arr->used_size; i++) {
        printf("%d ", (arr->ptr)[i]);
    }
    printf("\n");
}

// insert element at ith index (preserving order)
void insertElement(struct myArray *arr, int index, int value){
    if (arr->used_size == arr->total_size) {
        printf("Array is full, cant insert more elements");
        return;
    }
    else if (index > arr->total_size) {
        printf("index provided is outside the limits of array, Exiting.");
        return;
    }
    // else if (value > int_limits){
    //     printf("value provided is outside int limits, Exiting")
    //     return;
    // } // Implement int limits check
    for (int i=arr->used_size-1; i>=index; i--) {
        (arr->ptr)[i+1] = (arr->ptr)[i];
    }
    (arr->ptr)[index] = value;

    // updating used size
    arr->used_size += 1;
}

// sorted insertion (takes in a sorted array, automatically inserts the given element after the greatest member less than it)
// TODO

// delete element at ith index (preserves order)
void deleteElement(struct myArray *arr, int index){
    if (index > arr->total_size) {
        printf("index provided is outside the limits of array, Exiting.");
        return;
    }
    
    for (int i=index; i<arr->used_size-1; i++) {
        (arr->ptr)[i] = (arr->ptr)[i+1];
    }

    // updating used size
    arr->used_size -= 1;
}

int main()
{
    struct myArray marks;

    // demo of methods
    constructMyArray(&marks, 50);
    
    initializeMyArray(&marks);
    displayMyArray(&marks);
    
    insertElement(&marks, 4, 69);
    displayMyArray(&marks);
    
    deleteElement(&marks, 2);
    displayMyArray(&marks);

    destructMyArray(&marks);
    
    return 0;
}
