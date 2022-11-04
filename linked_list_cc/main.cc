#include "LL.h"

int main(){
    struct node* head_node = NULL;
    string var1 = "hello";
    string var2 = "bonjour";

    cout << "before add_node()\n";
    add_node(&head_node, var1);
    cout << "returned from add_node()\n";
    add_node(&head_node, var2);

    print_list(&head_node);
}