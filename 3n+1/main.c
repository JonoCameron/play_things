#include <stdio.h>
#include <stdlib.h>

static int i = 0;

/* Recursion is not a great idea, but since we aren't working with
 * embedded systems where we could run out of memory, it doesn't really matter.
 */

int threeNplus1(int n){
    /* 26 and 27 are good test numbers */
    /* If n == 1, return i */
    if(n == 1){
        return i;
    }
    /* If odd, (3*n+1), increment i, call again */
    /* If even, (n/2), increment i, call again */
    if(n % 2){
        n = (3 * n) + 1;
        i++;
        threeNplus1(n);
    }else{
        n = (n / 2);
        i++;
        threeNplus1(n);
    }
    return i;
};

int main(int argc, char* argv[]){
    int counter;
    int n = 0;
    printf("Program Name Is: %s\n",argv[0]);
    if(argc==1){
        printf("\nNo Extra Command Line Argument Passed Other Than Program Name\n");
    }
    n = atoi(argv[1]);
    if(n == 0){
        printf("Error: Input not converted to int, or you entered 0, which is pointless for 3n+1.\n");
        return -1;
    }

    threeNplus1(n);
    printf("The input %d, took %i iterations before resting at 1.\n", n, i);

    return 0;
}