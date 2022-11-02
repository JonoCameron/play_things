#include <iostream>
#include <cstring>

using namespace std;

/* Declaration of some classes to be defined in hashmap_library.cc. */
class value_node;
class bucket_node;

/* Declare a head bucket which will be the entry point to the hash table. */
static class bucket_node* entry_point = NULL;

///////////////////////////////////////////////////////////////////////////
/* Functions for linked list */
///////////////////////////////////////////////////////////////////////////
void hello_library();



/* Print functions */

int print_map();
int print_buckets();
int print_compression_number();



/* Delete functions */

int delete_value(int key, char** value);
int delete_bucket(bucket_node* head_node);



/* Add elements functions */

int add_bucket(int compression_number);
int add_value(string &value);



///////////////////////////////////////////////////////////////////////////
/* Algorithms for creating checksums and compression numbers */
///////////////////////////////////////////////////////////////////////////

int calc_checksum(string &value);
int* compress(int checksum, int* pIter);



///////////////////////////////////////////////////////////////////////////
/* Supporting functions */
///////////////////////////////////////////////////////////////////////////

