// implementing data structure and methods of last-in-first-out stack of int using array
#include <stdio.h>
#include <stdlib.h>

struct stack
{
    int size; // number of elements in the stack
    int top_index; // index of topmost element of stack
    int * store_array; // actual array where stack elements are stored
};

struct stack * createStack(int size) {
    struct stack * new_stack = (struct stack *) malloc(sizeof( struct stack));
    int * arr = (int*) malloc(size * sizeof(int));
    
    if (new_stack && arr) {
        new_stack->size = size;
        new_stack->top_index = -1;
        new_stack->store_array = arr;
    }
    
    return new_stack;
}

void deleteStack(struct stack * deletable_stack) {
    int* array_ptr = deletable_stack->store_array;
    
    if (array_ptr && deletable_stack) {
        free(array_ptr);
        free(deletable_stack);
        printf("stack deleted\n");
    }
    else {
        printf("null ptr encountered, memory not freed");
    }
}

int isEmpty(struct stack* check_stack) {
    if (check_stack->top_index == -1) {
        return 1;
    }
    return 0;
}

int isFull(struct stack * check_stack) {
    if (check_stack->top_index == check_stack->size - 1) {
        return 1;
    }
    return 0;
}

void push(struct stack * stack_ptr, int value) {
    if (isFull(stack_ptr)) {
        printf("Error: Stack Overflow\n");
    }
    else {
        stack_ptr->top_index++;
        stack_ptr->store_array[stack_ptr->top_index] = value;
    }
}

int pop(struct stack * stack_ptr) {
    if (isEmpty(stack_ptr)) {
        printf("Error: Stack Underflow\n");
        return -1;
    }
    else {
        int value = stack_ptr->store_array[stack_ptr->top_index];
        stack_ptr->top_index--; // no need to clear the array element also
        return value;
    }
}

int peek(struct stack * stack_ptr, int position_from_top) {
    int index = stack_ptr->top_index - position_from_top + 1;
    if (index < 0) {
        printf("Peeking Error: position entered is out of stack storage bounds\n");
        return -1;
    }
    else {
        return stack_ptr->store_array[index];
    }
}

// returns the topmost value of the stack (first out)
int stackTop(struct stack * stack_ptr) {
    return stack_ptr->store_array[stack_ptr->top_index];
}

// returns the bottom most value of the stack (last out)
int stackBottom(struct stack * stack_ptr) {
    return stack_ptr->store_array[0];
}

int main() {
    struct stack * myStack = createStack(5);

    printf("is empty - %d\n", isEmpty(myStack));
    printf("is full - %d\n", isFull(myStack));

    push(myStack, 5);

    printf("is empty - %d\n", isEmpty(myStack));
    printf("is full - %d\n", isFull(myStack));

    push(myStack, 7);
    push(myStack, 11);
    push(myStack, 13);
    push(myStack, 17);
    printf("peeking at posn 2 from top - %d\n", peek(myStack, 2));
    printf("is empty - %d\n", isEmpty(myStack));
    printf("is full - %d\n", isFull(myStack));

    push(myStack, 19);

    printf("%d\n", pop(myStack));
    printf("%d\n", pop(myStack));
    
    printf("peeking at posn 2 from top - %d\n", peek(myStack, 2));
    printf("stackTop %d\n", stackTop(myStack));
    printf("stackBottom %d\n", stackBottom(myStack));

    printf("%d\n", pop(myStack));
    printf("%d\n", pop(myStack));
    printf("%d\n", pop(myStack));
    printf("%d\n", pop(myStack));


    deleteStack(myStack);
    
    return 0;
}