#include "stdio.h"
#include "stdlib.h"

struct node
{
    int data;
    struct node* next;
    struct node* prev;
};

void push(struct node** head_node, int new_data);
void print_list(struct node** head_node);
void add_before(struct node** next_node, int new_data);
void add_after(struct node** prev_node, int new_data);
void append(struct node** head_node, int new_data);
void delete_node(struct node** head_node, struct node** dead_node);
void delete_list(struct node** head_node);