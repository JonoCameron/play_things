#include "linked_list.h"


int main(){
    /* Initialise the head node. */
    struct node* new_node = NULL;

    print_list(&new_node);

    /* Test append */
    append(&new_node, 1);

    /* Push 3 data points into list. */
    push(&new_node, 23);
    push(&new_node, 6);
    push(&new_node, 27);

    /* Print our new linked list. */
    print_list(&new_node);

    /* Add something two new data points to be index 2 and 3. */
    /* 8 will be index 1 */
    add_before(&new_node->next, 8);

    /* Add something after new node next */
    add_after(&new_node, 110);

    /* Do it again to try and break my function */
    add_after(&new_node->next, 111);

    /* Push another value to the front */
    push(&new_node, 10);
    print_list(&new_node);

    append(&new_node, 1);
    append(&new_node, 666);

    delete_node(&new_node, &new_node->next);

    /* Print our changed linked list. */
    print_list(&new_node);

    /* Delete everything */
    delete_list(&new_node);

    return 0;
}