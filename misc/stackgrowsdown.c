/* A file to demonstrate whether the stack grows up or down.
 * I've named the file stackgrowsdown.c because I think it
 * does. 
 */

#include <stdio.h>
#include <stdbool.h>

bool upordown(int* other){
    int x;

    if (!other) {
        return upordown(&x);
    } else {
        return &x > other;
    }
    
    
    return false;
}

int main(){
    int arr[7];
    

    printf("hello world.\n");

    printf("%s\n", upordown(NULL) ? "Up" : "Down");

    return 0;
}