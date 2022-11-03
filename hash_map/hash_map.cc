//#include <iostream>
#include "hashmap_library.h"

using namespace std;
//bucket_node* entry_point;

int main(){
    int i = 0;
    int* compression_number;
    int HC_checksum = 27;
    int test_checksum;
    bucket_node* entry_point = NULL;

    print_map(entry_point);
    string var = "bonjour";
    test_checksum = calc_checksum(var);

    compression_number = &i;
    compress(test_checksum, compression_number);
    add_value(entry_point, var);

    cout << "The compression number of the checksum " << test_checksum << " is: " << i << "\n";
    cout << "The value produced from the test_checksum was: " << test_checksum << "\n";
    hello_library();

    cout << "Entry_point->compression_number: ";

    cout << entry_point->compression_number << "\n";
//    print_map(entry_point);
    return 0;
}