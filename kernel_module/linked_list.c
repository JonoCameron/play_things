#include "linked_list.h"

void push(struct node** head_node, int new_data){
    /* Initialise node. */
    struct node* new_node = (struct node*)malloc(sizeof(struct node));

    /* Put data in new node */
    new_node->data = new_data;

    /* Set the next node as the old head node and the previous as NULL */
    new_node->next = *head_node;
    new_node->prev = NULL;

    /* If list is empty, initialise list. */
    if(*head_node != NULL){
        (*head_node)->prev = new_node;
    }

    /* Make the head of the list the new node. */
    *head_node = new_node;
};

void print_list(struct node** head_node){
    if(*head_node == NULL){
        printf("Lol empty list.\n");
        return;
    }
    struct node* new_node = *head_node;
    int num = 0;
    do{
        num = new_node->data;
        printf("%d ", num);
        new_node = new_node->next;
    }while(new_node != NULL);
    printf("\n");
};

void add_before(struct node** next_node, int new_data){
    if(next_node == NULL){
        printf("New node cannot be added before a NULL\n");
        return;
    }
    /* Initialise new node. */
    struct node* new_node = (struct node*)malloc(sizeof(struct node));

    /* Put data in new node */
    new_node->data = new_data;

    /* Set the new node prev to next node prev */
    new_node->prev = (*next_node)->prev;

    /* Set next node previous to new node */
    (*next_node)->prev = new_node;

    /* Set the new node next to following node */ 
    new_node->next = *next_node;

    /* Set the previous node next to our new node */
    new_node->prev->next = new_node;
};

void add_after(struct node** prev_node, int new_data){
    if(prev_node == NULL){
        printf("The previous node cannot be NULL.\n");
        return;
    }
    /* Initialise new node */
    struct node* new_node = (struct node*)malloc(sizeof(struct node));

    /* Put data in new node */
    new_node->data = new_data;

    /* Set the new node next to prev node next */
    new_node->next = (*prev_node)->next;

    /* Set the prev node next to new node */
    (*prev_node)->next = new_node;

    /* Set the new node prev to the prev node */
    new_node->prev = *prev_node;

    /* Set the next node prev to new node */
    new_node->next->prev = new_node;
};

void append(struct node** head_node, int new_data){
    /* Allocate new nodes */
    struct node* new_node = (struct node*)malloc(sizeof(struct node));

    struct node* last = (*head_node);

    /* Put data in new node */
    new_node->data = new_data;

    /* Appending so new node next is NULL */
    new_node->next = NULL;

    /* If list is empty, this is the head. */
    if((*head_node) == NULL){
        new_node->prev = NULL;
        *head_node = new_node;
        return;
    }

    /* Else if list is not empty, traverse to last spot. */
    while(last->next != NULL){
        last = last->next;
    }

    /* Set the next of the previous last node to last */
    last->next = new_node;

    /* Set the prev of new node to last */
    new_node->prev = last;

    return;
};

void delete_node(struct node** head_node, struct node** dead_node){
    /* Allocate new node */
    struct node* new_node = *head_node;

    /* Traverse until condemned node is found */
    while(new_node != *dead_node){
        new_node = new_node->next;
    }

    /* Set new node prev next to new node next */
    new_node->prev->next = new_node->next;

    /* Set new node next prev to new node prev */
    new_node->next->prev = new_node->prev;

    free(new_node);
};

void delete_list(struct node** head_node){
    /* Allocate new node */
    struct node* new_node = *head_node;

    /* Step and delete previous */
    while(new_node->next != NULL){
        new_node = new_node->next;
        free(new_node->prev);
    }

    /* Delete new_node, which should be the last node. */
    free(new_node);
}