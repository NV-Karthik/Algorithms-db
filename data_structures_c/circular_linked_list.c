// circular linked list (CLL) is just a linked list where the last node points to the first (head) node instead of pointing to NULL

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node
{
    int data;
    struct node* next;
};

// Create linked list by adding the head node
struct node* createLinkedList(int data) {
    struct node* head = (struct node*) malloc(sizeof(struct node));
    head->data = data;
    head->next = head; // the only node of CLL points to itself 
    return head;
}

// Traverse all nodes
void traverseList(struct node* head) {
    struct node* ptr = head; // donot update the head in case of CLL
    int num_nodes = 0;
    do {
        printf("%d ", ptr->data);
        ptr = ptr->next;
        num_nodes ++;
    }while (ptr != head);

    printf("\nNo of nodes = %d\n", num_nodes);
}

// sum of all data
int getSum(struct node* head) {
    int sum = 0;
    struct node* ptr = head;
    do {
        sum += head->data;
        ptr = ptr->next;
    } while(ptr != head);

    return sum;
}

// takes in value(data) in linked list gives out index of first node occuring with that value
int getIndex(struct node * head, int value) {
    int index = 0;
    struct node* ptr = head;
    do {
        if (ptr->data == value) {
            return index;
        }
        index ++;
        ptr = ptr->next;
    } while(ptr != head);
    return -1; // -1 gets returned if the reqd node is not found
}

// remove linked list and free all malloced space
// note that its important to remove each malloced node without losing pointers to other nodes
void freeLinkedList(struct node* head) {
    struct node* temp;
    struct node* ptr = head;
    // int count = 0; // uncomment these three lines for free-ing log
    do {
        temp = ptr;
        ptr = ptr->next;
        free(temp);
        // printf("freed node - %d\n", count);
        // count ++;
    } while(ptr != head);
    printf("Linked list erased from memory");
}

// ****** node append and insertion methods ******

/*
* note that current node is being passed as a value of pointer not as a reference,
* if i ever wanted the current node to be updated, I will pass the pointer by reference,
* ie., by using a pointer to a pointer (struct node **)
*/

// inserts node at the end of linked list
// in CCL append is just insert at beginning (insert at index == 0)
void appendNode(struct node* head, int data) {
    struct node* next_node = (struct node*) malloc(sizeof(struct node));
    struct node* index_ptr = head;

    do {
        index_ptr = index_ptr->next;
    } while(index_ptr->next != head);
    // linking current and next node
    index_ptr->next = next_node;
    
    // setting properties of next_node (now the current node)
    next_node->data = data;
    next_node->next = head;
}

// inserts node at a given index and returns the head node
struct node* insertNode(struct node* head, int index, int data) {
    struct node* ptr = (struct node *) malloc(sizeof(struct node));
    
    // insert at the beginning
    if (index == 0) {
        struct node* index_ptr;

        ptr->next = head; // assign old head as the next node of newly created node
        ptr->data = data; // assign given data to the new node

        // for CCL, traverse to the end of list and update old head to new head
        do {
            index_ptr = index_ptr->next;
        } while(index_ptr->next != head);
        index_ptr->next = ptr;

        return ptr; // rename the new node pointer as head (by assigning this to head in main)
    }
    // insert at a given index (also works as append function if last index is given)
    else {
        // updating current(head) node until i get to the node before reqd index
        struct node* current = head;
        for(int i=0; i < index-1; i++) {
            current = current->next; // this doesnot update head node's address refer note above

            // error handling
            if (current == head) {
                printf("Failure inserting node, index is out of linked list bounds\n");
                free(ptr);
                return head;
            }
        }
        // assign reqd data and next to new pointer (do this before step 3!!)
        ptr->next = current->next;
        ptr->data = data;
        
        // change next of prev node to point to our new node
        current->next = ptr;
        return head;
    }
}

// inserts node after the given (named previous) node (requires node address)
void insertAfter(struct node* previous_node, int data) {
    struct node* ptr = (struct node *) malloc(sizeof(struct node));

    ptr->next = previous_node->next;
    ptr->data = data;

    previous_node->next = ptr;
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
        struct node* index_ptr = head;
        
        // first taverse to the end and update the pointer pointing to head 
        do {
            index_ptr = index_ptr->next;
        } while(index_ptr->next != head);
        // now index_ptr points to last node
        index_ptr->next = head->next; // update last pointer
        head = head->next; // update head to the second node

        free(ptr); // erase old node
    }
    else if (index == -1)
    {
        printf("The element requested to delete is not found in linked list, exiting\n");
    }
    
    else {
        struct node* ptr_prev_node = head;
        struct node* ptr_ith_node;
        
        for (int i=0; i<index-1; i++){
            ptr_prev_node = ptr_prev_node->next;
        }
        ptr_ith_node = ptr_prev_node->next;

        ptr_prev_node->next = ptr_ith_node->next;
        free(ptr_ith_node);        
    }

    return head;
}

// similar to append, popNode donot require assigning it back to head node again
void popNode(struct node* head) {
    struct node* prev_node = head;
    struct node* curr_node = head->next;
    
    if (curr_node == head) {
        printf("The linked list seems to have only one node, and it is not removed use freeLinkedList method instead.");
        return;
    }

    while (curr_node->next != head) {
        prev_node = prev_node->next;
        curr_node = curr_node->next;
    } // after the loop curr node will be the last one, prev_node will be 1 node before it 

    prev_node->next = head;
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

    // testing insert after node at 4th index
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