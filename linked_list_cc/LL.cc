#include "LL.h"

void add_node(struct node** head_node, string &value){
    cout << "In add_node()\n";
    if(*head_node == NULL){
        cout << "head_node is NULL\n";
        *head_node = new node();
        (*head_node)->value = value;
        return;
    }
    cout << "Initialised head_node\n";
    struct node* tmp = *head_node;
    struct node* new_node = NULL;
    new_node = new node();
    cout << "made a new node\n";
    while(tmp->next != NULL){
        cout << "tmp->next\n";
        tmp = tmp->next;
    }
    new_node->value = value;
    tmp->next = new_node;

    return;
};

void print_list(struct node** head_node){
    struct node* tmp = *head_node;
    do{
        cout << tmp->value << "\n";
        tmp = tmp->next;
    }while(tmp);
    return;
}