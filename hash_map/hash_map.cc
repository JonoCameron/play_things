//#include <iostream>
#include "hashmap_library.h"

using namespace std;

int main(){
    int i = 0;
    int* compression_number;
    int HC_checksum = 27;
    int test_checksum;

    string var = "hello";
    test_checksum = calc_checksum(var);

    compression_number = &i;
    compress(test_checksum, compression_number);

    cout << "The compression number of the checksum " << test_checksum << " is: " << i << "\n";
    cout << "The value produced from the test_checksum was: " << test_checksum << "\n";
    hello_library();
    return 0;
}