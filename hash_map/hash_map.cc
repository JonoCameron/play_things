//#include <iostream>
#include "hashmap_library.h"

using namespace std;
//bucket_node* entry_point;

int main(){
    int i = 0;
    int* compression_number;
    int HC_checksum = 27;
    int test_checksum;
    struct bucket_node* entry_point = NULL;

    print_map(&entry_point);

    string var1 = "bonjour";

    add_value(&entry_point, var);

    hello_library();

    cout << "Entry_point->compression_number: " << entry_point->compression_number << "\n";
    print_map(&entry_point);
    return 0;
}