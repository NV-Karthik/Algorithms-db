// Doubly linked list (DLL) implementation with methods
// Doubly linked list will have a [prev -- data -- next] struct for each node

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node
{
    int data;
    struct node* prev;
    struct node* next;
};

// Create DLL by adding the head node
struct node* createLinkedList(int data) {
    struct node* head = (struct node*) malloc(sizeof(struct node));
    head->data = data;
    head->prev = NULL;
    head->next = NULL;
    return head;
}

// Traverse all nodes of DLL
void traverseList(struct node* head) {
    struct node* ptr = head;
    int num_nodes = 0;
    while (ptr != NULL) {
        printf("%d ", ptr->data);
        ptr = ptr->next;
        num_nodes ++;
    }

    printf("\nNo of nodes = %d\n", num_nodes);
}

// sum of all data
int getSum(struct node* head) {
    int sum = 0;

    while(head != NULL) {
        sum += head->data;
        head = head->next;
    }

    return sum;
}

// takes in value(data) in linked list gives out index of first node occuring with that value
int getIndex(struct node * head, int value) {
    int index = 0;
    while(head != NULL) {
        if (head->data == value) {
            return index;
        }
        index ++;
        head = head->next;
    }
    return -1; // -1 gets returned if the reqd node is not found
}

// remove linked list and free all malloced space
// note that its important to remove each malloced node without losing pointers to other nodes
void freeLinkedList(struct node* head) {
    struct node* temp;
    // int count = 0; // uncomment these three lines for free-ing log
    while(head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
        // printf("freed node - %d\n", count);
        // count ++;
    }
    printf("Doubly Linked List Freed");
}

// ****** node append and insertion methods ******

/*
* note that current node is being passed as a value of pointer not as a reference,
* if i ever wanted the current node to be updated, I will pass the pointer by reference,
* ie., by using a pointer to a pointer (struct node **)
*/

// inserts node at the end of linked list
// similar to popNode appendNode method donot require reassigning it to head pointer again
void appendNode(struct node* current_node, int data) {
    struct node* next_node = (struct node*) malloc(sizeof(struct node));
    
    while(current_node->next != NULL) {
        current_node = current_node->next;
    }
    // linking current and next node
    current_node->next = next_node;
    
    // setting properties of next_node (now the current node)
    next_node->data = data;
    next_node->prev = current_node;
    next_node->next = NULL;
}

// inserts node at a given index and returns the head node
struct node* insertNode(struct node* head, int index, int data) {
    struct node* ptr = (struct node *) malloc(sizeof(struct node));
    
    // insert at the beginning
    if (index == 0) {
        ptr->next = head; // assign old head as the next node of newly created node
        ptr->prev = NULL; // prev node of new head is null
        ptr->data = data; // assign given data to the new node

        // change prev of next node to point to our new node
        struct node * next_node = ptr->next;
        next_node->prev = ptr;

        return ptr; // rename the new node pointer as head (by assigning in main)
    }
    // insert at a given index (also works as append function if last index is given)
    else {
        // updating current(head) node until i get to the node before reqd index
        struct node* current = head;
        for(int i=0; i < index-1; i++) {
            current = current->next; // this doesnot update head node's address refer note above

            // error handling
            if (current == NULL) {
                printf("Failure inserting node, index is out of linked list bounds\n");
                free(ptr);
                return head;
            }
        }
        // assign reqd data and next to new pointer (do this before step 3!!)
        ptr->prev = current;
        ptr->next = current->next;
        ptr->data = data;
        
        // change next of prev node to point to our new node
        current->next = ptr;

        // change prev of next node to point to our new node
        struct node * next_node = ptr->next;
        if (next_node != NULL) {
            next_node->prev = ptr;
        } // this check is necessary to avoid crashes if last index is entered
        
        return head;
    }
}

// inserts node after a given node (requires node address)
void insertAfter(struct node* previous_node, int data) {
    struct node* ptr = (struct node *) malloc(sizeof(struct node));

    // assigning data for node to be inserted
    ptr->next = previous_node->next;
    ptr->data = data;
    ptr->prev = previous_node;

    // update previous node's next pointer
    previous_node->next = ptr;

    // update next node's previous pointer
    struct node* next_node = ptr->next;
    next_node->prev = ptr;
}

// ****** node deletion methods ******
// deletion involves updating links as well as freeing malloced memory

// the second argument isIndex should be set to true if index is being passed, set it to false if value is passed in 3rd arg
// passing value deletes the first node existing with that particular value
struct node* deleteNode(struct node* head, bool isIndex, int index_or_value) {
    
    int index;
    if (isIndex) {
        index = index_or_value;
    }
    else {
        index = getIndex(head, index_or_value);
    }

    // delete the beginning node
    if (index == 0) {
        struct node* ptr = head;
        head = head->next;
        free(ptr);
        head->prev = NULL;
    }
    else if (index == -1)
    {
        printf("The element requested to delete is not found in linked list, exiting\n");
    }
    
    else {
        struct node* ptr_prev_node = head;
        struct node* ptr_ith_node;
        struct node* ptr_next_node;
        
        for (int i=0; i<index-1; i++){
            ptr_prev_node = ptr_prev_node->next;
        }
        ptr_ith_node = ptr_prev_node->next;
        ptr_next_node = ptr_ith_node->next;

        ptr_prev_node->next = ptr_next_node;
        if (ptr_next_node != NULL) {
            ptr_next_node->prev = ptr_prev_node;
        } // this check is necessary to avoid crashes if last index is entered

        free(ptr_ith_node);        
    }

    return head;
}

// similar to append, popNode donot require assigning it back to head node again
void popNode(struct node* head) {
    struct node* prev_node;
    struct node* next_node;
    struct node* curr_node = head;
    while (curr_node->next != NULL) {
        curr_node = curr_node->next;
    } // after the loop the curr_node will be the last node 

    prev_node = curr_node->prev;

    prev_node->next = NULL;
    free(curr_node);
}

int main() {

    // create linked list
    struct node* myLL = createLinkedList(5);
    
    // add nodes
    appendNode(myLL, 7);
    appendNode(myLL, 13);
    appendNode(myLL, 1);

    // traverse and display nodes
    traverseList(myLL);

    // insert new elem at index 0 (beginning)
    myLL = insertNode(myLL, 0, 0);
    printf("display after adding 0 as first node\n");
    traverseList(myLL);

    // insert new elem at index 2 (beginning)
    myLL = insertNode(myLL, 2, 0);
    printf("display after adding 0 as third node\n");
    traverseList(myLL);

    // num nodes = 6 by now, index of node which will be last = 6 
    myLL = insertNode(myLL, 6, 99);
    printf("display after adding 99 as last node\n");
    traverseList(myLL);

    // testing insertAfter node at 4th index
    struct node* address = myLL;
    for (int i=0; i<4; i++) {
        address = address->next;
    }
    insertAfter(address, 360);
    printf("display after insertAfter index 4\n");
    traverseList(myLL);

    printf("index of %d is %d\n\n\n\n", 360, getIndex(myLL, 360));

    // deletion methods
    myLL = deleteNode(myLL, true, 0);
    printf("display after delete index 0\n");
    traverseList(myLL);

    myLL = deleteNode(myLL, true, 3);
    printf("display after delete index 3\n");
    traverseList(myLL);

    myLL = deleteNode(myLL, true, 5);
    printf("display after delete index last\n");
    traverseList(myLL);

    popNode(myLL);
    printf("display after pop node\n");
    traverseList(myLL);

    myLL = deleteNode(myLL, false, 7);
    printf("display after delete value 7\n");
    traverseList(myLL);

    myLL = deleteNode(myLL, false, 69);

    // free memory created for linked list
    freeLinkedList(myLL);

    return 0;
}