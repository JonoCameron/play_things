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
    string var2 = "hi";
    string var3 = "hello";

    add_value(&entry_point, var1);
    add_value(&entry_point, var2);
    add_value(&entry_point, var3);

    hello_library();

    // cout << "Entry_point->compression_number : " << entry_point->compression_number << "\n";
    // cout << "Entry_point->value->value : " << entry_point->value->value << "\n"; 
    print_map(&entry_point);
    return 0;
}