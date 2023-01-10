#include "main.h"

int main(){
    int a = 3;
    for (int i = 0; i < a; i++){
        say_hello();
    }

    printf("%3d\n", a); // Fancy that, it prints two spaces. (From my Sportable interview).

    return 0;
}