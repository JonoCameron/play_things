#include "hashmap_library.h"

void hello_library(){
    cout << "Hello from the function library!\n";
    return;
}

/* Traverse key node, then print each value.
 *
 * [key1]->[value1]->[value2]->etc
 * ↓
 * [key2]->[value2]->etc
 * ↓
 * etc
 */
int print_map(bucket_node* entry_point){
    if(entry_point == NULL){
        cout << "The hash table is empty.\n";
        return -1;
    }

    bucket_node* tmp_bucket = entry_point;
    value_node* tmp_value = tmp_bucket->value;
    do{
        cout << "Key: " << entry_point->compression_number << " -> ";
        do{
            cout << tmp_value->value << " -> ";
            tmp_value = tmp_value->next_node;
        }while(tmp_value->next_node);
        cout << "\n";
    }while(tmp_bucket->next_node);
    return 0;
};

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
int add_value(bucket_node* entry_point, string &value){
    bucket_node* tmp_entry = entry_point;
    value_node* new_node;

    /* If this is the first entry, create the entry point, then have its
     * value_node pointer set to the new value node 
     */
    if(tmp_entry == NULL){
        /* Initialise two new nodes. */
        tmp_entry = (bucket_node*)malloc(sizeof(bucket_node));
        new_node = (value_node*)malloc(sizeof(value_node));

        /* Fill data points */
        init_bucket(tmp_entry, value);

        init_value(new_node, value);

        /* Link the two nodes */
        bucket_to_node(tmp_entry, new_node);

        // /* Set entry_point to point to tmp_entry */
        entry_point = tmp_entry;

        cout << "\nThe entry points key is: " << entry_point->compression_number << "\n";
        cout << "The entry point's address is: " << entry_point << "\n";
        cout << "\nThe new nodes value is: " << new_node->value << "\n";
        cout << "The new nodes key is: " << new_node->key << "\n";
        cout << "The new nodes compression number is: " << new_node->compression_number << "\n";
        cout << "The new nodes bucket address is: " << new_node->bucket << "\n\n";

        return 0;
    }

    return 0;
};


///////////////////////////////////////////////////////////////////////////
/* Algorithms for creating checksums and compression numbers */
///////////////////////////////////////////////////////////////////////////

/* Produce a key/checksum of the value string. */
int calc_checksum(string &value){
    int checksum = 0;
    int tmp = 0;

    for(int i = 0; i < value.length(); i++){
        tmp = (unsigned char)value[i];
        checksum = checksum + tmp;
    }
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



///////////////////////////////////////////////////////////////////////////
/* Supporting functions */
///////////////////////////////////////////////////////////////////////////

bool bucket_exists(int compression_number, bucket_node* pBucket);

void init_bucket(bucket_node* tmp_entry, string &value){
    int i = 0;
    int* compression_number = &i;
    int key = calc_checksum(value);

    tmp_entry->compression_number = *(compress(key, compression_number));

    return;
};

void init_value(value_node* new_node, string &value){
    int i = 0;
    int* compression_number = &i;

    new_node->key = calc_checksum(value);
    new_node->compression_number = *(compress(new_node->key, compression_number));
    new_node->value = value;

    return;
};

void bucket_to_node(bucket_node* pBucket, value_node* pValue){
    pBucket->value = pValue;
    pValue->bucket = pBucket;

//    cout << "linking nodes... entry_point->compression_number: " << entry_point->compression_number << "\n";

    return;
};
