#include "hashmap_library.h"

class bucket_node{
    public:
    int compression_number;
    bucket_node* next_node = NULL;
    bucket_node* prev_node = NULL;
    value_node* value = NULL;
};

class value_node{
    public:
    int key;                                // The key/checksum of the value.
    int compression_number;                 // The compressed key.
    string value;                           // The given string.
    value_node* next_node = NULL;           // The pointer to the next key-value pair in the LL, if it exists.
    value_node* prev_node = NULL;           // The pointer to the previous key-value pair in the LL, if it exists.
    bucket_node* bucket = NULL;         /* The list head, which points to the "bucket" this value is stored in. \
                                             * always exist if this node exists.
                                             */
};

void hello_library(){
    cout << "Hello from the function library!\n";
    return;
}

int print_map();

/* Print out just the buckets that exist. The implementation of this
 * should probably be better that walking a LL. Maybe have a bitmap
 * stores all of them?
 */
int print_buckets();

/* A function that prints out all values that share the same bucket */
int print_compression_number();

/* Delete functions */

/* Find key value pair, link nodes previous and next nodes, then
 * free the memory of the node that was there
 */ 
int delete_value(int key, char** value);

/* Traverse key node, then delete the value nodes. Then hop to the
 * next key node.
 */
int delete_bucket(bucket_node* head_node);

/* Add elements functions */

/* Add a bucket to the list of buckets */
int add_bucket(int compression_number);

/* Create node, initialise fields, link to the rest of the list.
 * The node will be added to its bucket by its compression number
 * but will be sorted in the bucket by its checksum.
 */
int add_value(string &value);


///////////////////////////////////////////////////////////////////////////
/* Algorithms for creating checksums and compression numbers */
///////////////////////////////////////////////////////////////////////////

/* Produce a checksum of the value string. */
int calc_checksum(string &value){
    int checksum = 0;
    int tmp = 0;
    cout << value << " from the checksum function\n";

    for(int i = 0; i < value.length(); i++){
        tmp = (unsigned char)value[i];
        cout << value[i] << " has the decimal value of: " << tmp << "\n";
        checksum = checksum + tmp;
    }
    cout << "\n";
    return checksum;
};

/* Produce a compression number from the checksum. This will be recursive,
 * be wary of this. A future improvement for this would be to not do that.
 * For now, rip this code from the 3n+1 directory.
 * 
 * Oh God we haven't even thought about how to mitigate negatives... Surely
 * an if() will suffice??
 */
int* compress(int checksum, int* pIter){
    if(checksum == 1){
        return pIter;
    }
    if(checksum < 1){
        cout << "Somehow, your input resulted in a checksum of 0 or -1\n";
        return pIter; 
    }

    if(checksum % 2){
        checksum = (3 * checksum) + 1;
        (*pIter)++; // Check out that pointer arithmetic!
        compress(checksum, pIter);
    }else{
        checksum = (checksum / 2);
        (*pIter)++;
        compress(checksum, pIter);
    }
    return pIter;
};