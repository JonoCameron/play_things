//#include <iostream>
#include "hashmap_library.h"

using namespace std;

int main(){
    int i = 0;
    int* compression_number;
    int HC_checksum = 27;
    int test_checksum;

    print_map();
    string var = "bonjour";
    test_checksum = calc_checksum(var);

    compression_number = &i;
    compress(test_checksum, compression_number);
    add_value(var);

    cout << "The compression number of the checksum " << test_checksum << " is: " << i << "\n";
    cout << "The value produced from the test_checksum was: " << test_checksum << "\n";
    hello_library();

    cout << "Entry_point->compression_number: ";
    cout << entry_point->compression_number << "\n";
//    print_map();
    return 0;
}