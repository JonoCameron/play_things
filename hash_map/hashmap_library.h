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

int print_map(bucket_node* entry_point);
int print_buckets();
int print_compression_number();


/* Delete functions */

int delete_value(int key, char** value);
int delete_bucket(bucket_node* head_node);


/* Add elements functions */

int add_bucket(int compression_number);
int add_value(bucket_node* entry_point, string &value);


///////////////////////////////////////////////////////////////////////////
/* Algorithms for creating checksums and compression numbers */
///////////////////////////////////////////////////////////////////////////

int calc_checksum(string &value);
int* compress(int checksum, int* pIter);


///////////////////////////////////////////////////////////////////////////
/* Supporting functions */
///////////////////////////////////////////////////////////////////////////

bool bucket_exists(int compression_number);
void init_bucket(bucket_node* tmp_entry, string &value);
void init_value(value_node* new_node, string &value);
void bucket_to_node(bucket_node* pBucket, value_node* pValue);

