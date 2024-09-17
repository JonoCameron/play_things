#include "stdio.h"
#include "stdlib.h"

int** generate(int numRows, int* returnSize, int** returnColumnSizes);
int calc_returnSize(int n, int* returnSize);
int* calc_returnColumnSizes(int n, int** returnColumnSizes);

int main(int argc, char *argv[]){
    int numRows = 0;
    int NoE = 1;
    int *returnSize = &NoE;
    int **returnColumnSizes;
    
    if(argc == 1){
        printf("Please give command line argument.\n");
        return -1;
    }else if(atoi(argv[1]) <= 0){
        printf("Please give argument greater than 0.\n");
        return -1;
    }else{
        numRows = atoi(argv[1]);
    }
    *returnSize = calc_returnSize(numRows, returnSize);
    returnColumnSizes = (int**)calloc(numRows, sizeof(int*));

    for(int i = 0; i < numRows; i++){
        returnColumnSizes[i] = (int*)calloc(i + 1, sizeof(int));
    }

    returnColumnSizes[1][0] = 383;

    returnColumnSizes = generate(numRows, returnSize, returnColumnSizes);
    
    printf("You want %d rows of Pascal's Triangle. ", numRows);
    printf("%d rows will create an array of %d elements.\n", numRows, *returnSize);
    int rowLength = 1;
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < rowLength; j++){
            printf("%d ", returnColumnSizes[i][j]); //problem at NoE
        }
        rowLength++;
        printf("\n");
    }

    return 0;
}

int** generate(int numRows, int* returnSize, int** returnColumnSizes){
    int rowLength = 1;
    int i = 0;
    for(int j = 0; j < numRows; j++){
        for(int k = 0; k < rowLength; k++){
            if(k == 0){
                returnColumnSizes[j][k] = 1;
            }
            if(k == (rowLength - 1)){
                returnColumnSizes[j][k] = 1;
            }else{
                returnColumnSizes[j][k] = returnColumnSizes[j-1][k-1] + returnColumnSizes[j-1][k];
            }
        }
        rowLength++;
    }
    return returnColumnSizes;
};

int calc_returnSize(int n, int* returnSize){
    if(n != 0){
        *returnSize = *returnSize + n;
        calc_returnSize(n - 1, returnSize);
    }else{
        return *returnSize;
    }
};

