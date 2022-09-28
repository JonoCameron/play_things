#include <stdio.h>
#include <stdlib.h>

void sort_colours(int* nums, int numsSize){
    
    int zero = 0;
    int ones = 0;
    int twos = 0;

    for (int i = 0; i < numsSize; i++){
        if(nums[i] == 0){
            zero++;
        }
        else if(nums[i] == 1){
            ones++;
        }
        else{
            twos++;
        }
    }
    for (int i = 0; i < zero; i++){
        nums[i] = 0;
    }
    for (int i = zero; i < zero + ones; i++){
        nums[i] = 1;
    }
    for (int i = zero + ones; i < numsSize; i++){
        nums[i] = 2;
    }
}

int main(){
    
    int numsSize = 5;
    int arr[] = {2, 1, 0, 2, 1};

    printf("The colour array given:\n");
    for(int i = 0; i < numsSize; i++){
        printf("%d, ", arr[i]);
    }
    
    sort_colours(arr, numsSize);

    printf("\nThe colour array sorted:\n");
    for(int i = 0; i < numsSize; i++){
        printf("%d, ", arr[i]);
    }
    printf("\n");
    return 0;
}