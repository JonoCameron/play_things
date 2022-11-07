//#include <iostream>
#include "hashmap_library.h"

using namespace std;
//bucket_node* entry_point;

int main(int argc, char* argv[]){
    int i = 0;
    int* compression_number;
    int HC_checksum = 27;
    int test_checksum;
    struct bucket_node* entry_point = NULL;

    print_map(&entry_point);

    string var1 = "bonjour";
    string var2 = "hi";
    string var3 = "hello";
    string var4 = "bonjour";

    add_value(&entry_point, var1);
    add_value(&entry_point, var2);
    add_value(&entry_point, var3);
    add_value(&entry_point, var4);

    print_map(&entry_point);
    return 0;
}