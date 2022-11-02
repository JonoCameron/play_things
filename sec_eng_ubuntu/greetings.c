/*
* Compile this program with 'make greetings'; run it with ./greetings
*
* A simple program to say hello and get to know the user better.
*
*/
#define _GNU_SOURCE
#pragma GCC diagnostic ignored "-Wformat"
#pragma GCC diagnostic ignored "-Wformat-security"
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*
 * This function here is a dummy that I used to explore the execution 
 * path of the process whilst investigating the process with GDB.
 */
void hijack(void){
    system("/bin/sh");
}

char upper(char c) {
    return c & ~0x20;
}

char lower(char c) {
    return c | 0x20;
}

char* getinput(char *prompt) {
    char input[32];
    char *ret;

again:
    printf(prompt);
    if(!gets(input))
    goto again;

    ret = malloc(strlen(input));
    strcpy(ret, input);
    return ret;
}

char *uppercase(char *s) {
    int i;
    char *o = malloc(strlen((s)));
    strcpy(o, s);
    
    for (i=0; i<strlen(o); i++) {
        o[i] = upper(o[i]);
    }
    
    return o;
}

int main(int argc, char* argv[]) {
    char *name;
    char *friendlyprompt;
    char *icecream;
    char *pizza;
    char *filename;
    char *command;

    name = getinput("Welcome, what is your name: ");

    asprintf(&friendlyprompt, "%s, what is your favourite ice cream: ", name);

    icecream = getinput(friendlyprompt);

    asprintf(&friendlyprompt, "%s! I love %s ice cream too. What's ""your favourite pizza, %s? ",\
        uppercase(icecream), icecream, name);

    pizza = getinput(friendlyprompt);

    asprintf(&friendlyprompt, "%s is a good pizza topping.\n", pizza);
    printf(friendlyprompt);

    asprintf(&filename, "/tmp/%s", name);
    asprintf(&command, "echo 'It was a pleasure to meet you, %s' >> %s", name, filename);

    asprintf(&friendlyprompt, "I've left you a present in %s\n", filename);
    printf(friendlyprompt);
    
    system(command);
    
    exit(0);
}
