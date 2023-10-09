/* https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format */

#include "stdio.h"

typedef unsigned short U8;
typedef long long ll;

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0')

void bitwise_print(long num){
   printf("another way to num: %d\n", sizeof(long)*4);
   for(int i = (sizeof(long)*4)-1; i >= 0; i--){
      printf("%c", (num >> i) & 1 ? '1' : '0');
   }
   printf("\n");
}

int main(){
   U8 num = 0xaa;
   int bignum = 0xaaaaaaaa;

   printf("num in binary     : "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(num));
   printf("\n");

   bitwise_print(num);
   bitwise_print(bignum);

   return 0;
}
