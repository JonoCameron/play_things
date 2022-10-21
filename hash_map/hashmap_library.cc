#include "hashmap_library.h"

void hello_library(){
    std::cout << "Hello from the function library!\n";
    return;
}

void push_key(int key, char* value){
    class node* new_node = (node*)malloc(sizeof(node));
    class node* tmp = head_node;
    class node* prev;

    new_node->key = key;
    memcpy(new_node->value, value, VALUE_LENGTH);
    
    if(head_node == NULL){
        head_node = new_node;
        return;
    }

    if(head_node->key_below == NULL){
        head_node->key_below = new_node;
        new_node->key_above = head_node;
        return;
    }

    while(new_node->key < tmp->key){
        tmp = tmp->key_below;
        prev = tmp->key_above;
    }
    
    new_node->key_below = prev->key_below;
    new_node->key_above = prev;
    prev->key_below = new_node;
    tmp->key_above = new_node;

    return;
};

void print_list(){
    return;
};

void delete_node(int key, char** value){
    return;
};

void delete_list(node* head_node){
    return;
};