#include <iostream>
#include <cstring>

using namespace std;

class bucket_node;
class value_node;

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
    bucket_node* bucket = NULL;             // The list head, which points to the "bucket" this value is stored in.
                                             
};

/* Declare a head bucket which will be the entry point to the hash table. */
//extern bucket_node* entry_point;

///////////////////////////////////////////////////////////////////////////
/* Functions for linked list */
///////////////////////////////////////////////////////////////////////////
void hello_library();


/* Print functions */

int print_map(struct bucket_node** entry_point);
int print_buckets();
int print_compression_number();


/* Delete functions */

int delete_value(int key, char** value);
int delete_bucket(bucket_node* head_node);


/* Add elements functions */

int add_bucket(int compression_number);
int add_value(struct bucket_node** entry_point, string &value);
int push_bucket(struct bucket_node** entry_point, struct bucket_node** new_bucket);


///////////////////////////////////////////////////////////////////////////
/* Algorithms for creating checksums and compression numbers */
///////////////////////////////////////////////////////////////////////////

int calc_checksum(string &value);
int* compress(int checksum, int* pIter);


///////////////////////////////////////////////////////////////////////////
/* Supporting functions */
///////////////////////////////////////////////////////////////////////////

bool bucket_exists(int compression_number, struct bucket_node** entry_point);
void init_bucket(struct bucket_node** new_bucket, string &value, int key);
void init_value(struct value_node** new_node, string &value, int key);
void bucket_to_node(struct bucket_node** pBucket, struct value_node* pValue);

// cout << "\nThe entry point's key is: " << (*entry_point)->compression_number << "\n";
// cout << "The entry point's address is: " << entry_point << "\n";
// cout << "\nThe new nodes value is: " << new_node->value << "\n";
// cout << "The new nodes key is: " << new_node->key << "\n";
// cout << "The new nodes compression number is: " << new_node->compression_number << "\n";
// cout << "The new nodes bucket address is: " << new_node->bucket << "\n\n";