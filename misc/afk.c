// afk.c
// I think you can work out what this is for...
#include "stdio.h"

int main(){
	int a = 0;
	int T = 0, t = 0;
	while(1){
      if(T == 0 && t == 0){
         printf("\rYou've not been gone long.");
      }
      fflush(stdout);
      printf("\r                                           ");
		for(int i = 0; i < 1<<15; i++){
			printf("\rTick. (0 )(0 )");
			fflush(stdout);
			a = a + 1;
		}

		a = 0;
      t++;

		for(int i = 0; i < 1<<15; i++){
			printf("\rTock. ( 0)( 0)");
			fflush(stdout);
			a = a + 1;
		}
      a = 0;
		T++;
      if(T % 1000 == 0 && t % 1000 == 0){
         printf("\nYou've been gone for a while, friend.\n");
      }
	}
	return 0;
}
