#include "stdio.h"
#include "string.h"
#include "math.h"
#include "stdlib.h"

int main(int argc, char** argv){
    printf("What is a rational number?\n\n");
    double d;
    if(argc == 1){
        printf("A rational number is a number that can be expressed as the ratio of two\n");
        printf("integers, where the denominator is non-zero. It can be written as a/b, \n");
        printf("where a and b are integers and b is non-zero. \nProvide a ratio to see if");
        printf(" it is rational\n");
        return 0;
    }else{
        printf("You gave the ratio %lf, I will now tell you if it is rational\n\n", strtod(argv[1], NULL));
        d = strtod(argv[1], NULL);
    }

    return 0;
}