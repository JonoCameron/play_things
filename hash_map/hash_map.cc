/* An implementation of a hashmap. This will probably require
 * a main.cc, function_library.cc and header_file.h to keep
 * code organised and scalable.
 * 
 * This hashmap will be implemented to handle many-to-one
 * mappings, however that works.... The idea is that no value
 * should be lost or over-written. Therefore, if a key gets a 
 * second value, the compression function will find another 
 * box for the value. The inverse will happen when getting
 * key-value pairs; the get function will check that key and
 * compressions associated with it to return more than one
 * result.
 * 
 * Having done a single Google, the hash-table may be a bit
 * better for what I want to do... 
 * 
 * I want to have a linked-list of keys, where each node has a
 * pointer to the head of a new linked-list. This subsequent 
 * linked-list will link each value associated with the key. 
 * Then the get function will return the list of the key-value
 * pairs.
 * 
 * So first, an implementation of a linked list in C++. Probably
 * doubly linked, we can add and delete nodes. This LL will need
 * Add, print, and delete. Add will have the logic to add in the 
 * correct order so the list will be build sorted and not need a 
 * sort function.
 */

//#include <iostream>
#include "hashmap_library.h"

using namespace std;

int main(){
    string var = "hello";
    hello_library();
    push_key(5, var);
    cout << "returned from push_key\n";
    return 0;
}