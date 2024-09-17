#include "stdio.h"
#include "string.h"
#include "math.h"
#include "stdlib.h"

int* case1(double R, int* couple);
int* case2(double R, int* couple);
int* case3(double R, int* couple);
int* case4(double R, int* couple);

int main(int argc, char** argv){
    printf("What is a rational number?\n\n");
    double R;
    int* couple = (int*)calloc(2, sizeof(int));
    couple[0] = 0;
    couple[1] = 0;
    if(argc == 1){
        printf("A rational number is a number that can be expressed as the ratio of two\n");
        printf("integers, where the denominator is non-zero. It can be written as a/b, \n");
        printf("where a and b are integers and b is non-zero. \nProvide a ratio to see if");
        printf(" it is rational\n");
        return 0;
    }else{
        R = strtod(argv[1], NULL);
        printf("You gave the Real number, R = %lf, I will now tell you what two \n", R);
        printf("intergers R is a ratio of.\n\n");
    }
    if(R < -1){
        printf("R < -1\n");
        couple = case2(R, couple);
    }else if(R >= -1 && R < 0){
        printf("-1 <= R < 0\n");
        couple = case2(R, couple);
    }else if(R >= 0 && R < 1){
        printf("0 <= R < 1\n");
        couple = case4(R, couple);
    }else{
        printf("R >= 1\n");
        couple = case4(R, couple);
    }

    printf("R = %lf is a ratio of %d / %d.\n", R, couple[0], couple[1]);

    return 0;
}

int* case1(double R, int* couple){
    return couple;
};

int* case2(double R, int* couple){
    int a = couple[0];
    int b = couple[1];
    double quotient;
    if(a == 0 && b == 0){
        // First iteration. Cast R as an integer and set a to value of (int)R.
        a = -1;
        b = 1;
    }
    quotient = (double)a / (double)b;
    if(quotient == R){
        couple[0] = a;
        couple[1] = b;
        return couple;
    }
    if(quotient > R){
        a = a - 1;
        couple[0] = a;
        couple[1] = b;
        couple = case2(R, couple);
    }
    if(quotient < R){
        b = b + 1;
        couple[0] = a;
        couple[1] = b;
        couple = case2(R, couple);
    }
    return couple;
};

int* case3(double R, int* couple){
    return couple;
};

int* case4(double R, int* couple){
    int a = couple[0];
    int b = couple[1];
    double quotient;
    if(a == 0 && b == 0){
        // First iteration. Cast R as an integer and set a to value of (int)R.
        a = (int)R;
        b = 1;
    }
    quotient = (double)a / (double)b;

    if(quotient == R){
        couple[0] = a;
        couple[1] = b;
        return couple;
    }
    if(quotient > R){
        b = b + 1;
        couple[0] = a;
        couple[1] = b;
        couple = case4(R, couple);
    }
    if(quotient < R){
        a = a + 1;
        couple[0] = a;
        couple[1] = b;
        couple = case4(R, couple);
    }
    return couple;
};