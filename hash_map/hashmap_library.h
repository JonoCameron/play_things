#include <iostream>
#include <cstring>

using namespace std;
#define VALUE_LENGTH 32

class node{
    public:
    int key;
    int key_hash;
    string value;
    // char value[VALUE_LENGTH];
    node* key_above = NULL;
    node* key_below = NULL;
    node* next_node = NULL;
    node* prev_node = NULL;
};

static class node* head_node = NULL;

/* Functions for linked list */
void hello_library();

/* Create node, initialise fields, link to the rest of the list. */
void push_key(int key, string &value);

/* Traverse key node, then print each value.
 *
 * [key1]->[value1]->[value2]->etc
 * ↓
 * [key2]->[value2]->etc
 * ↓
 * etc
 */
void print_list();

/* Find key value pair, link nodes previous and next nodes, then
 * free the memory of the node that was there
 */ 
void delete_key(int key, char** value);

/* Traverse key node, then delete the value nodes. Then hop to the
 * next key node.
 */
void delete_list(node* head_node);

/* Functions for hashing. Probably not a lot going on here, since
 * the data structure is going to have a dynamic size. Maybe the
 * leading number of the key becomes the map, so the hash table 
 * only has a size of 10?
 */

