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
int print_map(struct bucket_node** entry_point){
    if(*entry_point == NULL){
        cout << "The hash table is empty.\n";
        return -1;
    }
    struct bucket_node* tmp_bucket = *entry_point;
    struct value_node* tmp_value = tmp_bucket->value;
    do{
        tmp_value = tmp_bucket->value;
        cout << "Key: " << tmp_bucket->compression_number << " -> ";
        do{
            cout << tmp_value->value << " -> ";
            tmp_value = tmp_value->next_node;
        }while(tmp_value);
        cout << "NULL\n";
        tmp_bucket = tmp_bucket->next_node;
    }while(tmp_bucket);
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
int add_value(struct bucket_node** entry_point, string &value){
    struct value_node* new_node;
    struct bucket_node* new_bucket;
    struct bucket_node* tmp;
    int i = 0;
    int* pIter = &i;
    int checksum = calc_checksum(value);
    int key = *(compress(checksum, pIter));

    /* If this is the first entry, create the entry point, then have its
     * value_node pointer set to the new value node 
     */
    if(*entry_point == NULL){
        cout << "The bucket for key " << key << " does not exist. Making a new one...\n";
        
        /* Initialise two new nodes. */
        *entry_point = new bucket_node();
        new_node = new value_node();

        /* Fill data points */
        init_bucket(entry_point, value, checksum);

        init_value(&new_node, value, checksum);

        /* Link the two nodes */
        bucket_to_node(entry_point, new_node);

        return 0;
    }
    
    tmp = *entry_point;
    
    /* Check out whether we need a new bucket */
    if(bucket_exists(key, entry_point)){
        // cout << "Say hello " << value <<"\n";

        new_node = new value_node();
        init_value(&new_node, value, checksum);
        find_bucket(&tmp, checksum);
        //cout << "in add value, tmp->compression_number: " << tmp->compression_number << "\n";

        append_value(&tmp->value, &new_node);
    }else{
        cout << "The bucket for key " << key << " does not exist. Making a new one...\n";

        /* Initialise nodes */
        new_bucket = new bucket_node();
        new_node = new value_node();
        init_bucket(&new_bucket, value, checksum);
        init_value(&new_node, value, checksum);

        /* Link nodes */
        bucket_to_node(&new_bucket, new_node);

        /* Push to top of bucket LL */
        push_bucket(entry_point, &new_bucket);
    }

    return 0;
};

int push_bucket(struct bucket_node** entry_point, struct bucket_node** new_bucket){
    (*entry_point)->prev_node = *new_bucket;
    (*new_bucket)->next_node = *entry_point;
    *entry_point = *new_bucket;
    return 0;
};

int append_value(struct value_node** head_value, struct value_node** new_value){
    //cout << "In append value. : " << (*head_value)->value << "\n";
    while((*head_value)->next_node != NULL){
        (*head_value) = (*head_value)->next_node;
    }
    (*head_value)->next_node = (*new_value);
    (*new_value)->prev_node = (*head_value);
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


bool bucket_exists(int compression_number, struct bucket_node** entry_point){
    struct bucket_node* tmp = *entry_point;
    do{
        if(tmp->compression_number == compression_number){
            return true;
        }
        tmp = tmp->next_node;
    }while(tmp);
    return false;
};

int find_bucket(struct bucket_node** tmp_bucket, int key){
    while((*tmp_bucket)->next_node != NULL){
        cout << "Searching...\n";
        (*tmp_bucket) = (*tmp_bucket)->next_node;
        
    }
    //cout << "in find bucket, tmp->compression_number: " << (*tmp_bucket)->compression_number << "\n";

    return 0;
};

void init_bucket(struct bucket_node** new_bucket, string &value, int key){
    int i = 0;
    int* compression_number = &i;
//    int key = calc_checksum(value);

    (*new_bucket)->compression_number = *(compress(key, compression_number));

    return;
};

void init_value(struct value_node** new_node, string &value, int key){
    int i = 0;
    int* compression_number = &i;

    (*new_node)->key = key;
    (*new_node)->compression_number = *(compress((*new_node)->key, compression_number));
    (*new_node)->value = value;

    return;
};

void bucket_to_node(bucket_node** pBucket, value_node* pValue){
    (*pBucket)->value = pValue;
    pValue->bucket = *pBucket;

    return;
};
