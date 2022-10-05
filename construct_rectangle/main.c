#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* constructRectangle(int area, int* returnSize){
    printf("here\n");
    int* arr;
    printf("ohno\n");
    arr = (int*)malloc(2 * sizeof(int));
    printf("where");
    *returnSize = 2;
    int w = sqrt(area);
    
    while(w){
        if(!(area%w)){
            *arr = area/w;
            *(arr + 1) = w;
            break;
        }
    }

    printf("hello, %d, %d\n", *arr, *(arr + 1));
    return arr;
}

int main(){
    int area = 42;
    int* retSize = 0;
    printf("there\n");
    constructRectangle(area, retSize);
    //printf("hello, %d, %d", arr[0], arr[1]);
    return 0;
}