#include <iostream>
#include <cstring>

using namespace std;

class node{
    public:
    node* next = NULL;
    string value;
};

void add_node(struct node** head_node, string &value);
void print_list(struct node** head_node);