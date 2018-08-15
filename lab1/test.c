#include <stdio.h>

int bitCount(int x) {
  /* This is a good one. So we first must create a mask of 00010001
     repeat to help us compute the number of 1 bits within our first
     four bits. Then we use the variable newmask and by continually
     shifting by 4 and &-ing to help determine our final sum! */
  int halfmask = 0x11 | (0x11 << 8);
  int fullmask = halfmask | (halfmask << 16);
  
  int sum = x & fullmask;
  sum = sum + (fullmask & (x >> 1));
  sum = sum + (fullmask & (x >> 2));
  sum = sum + (fullmask & (x >> 3));
  
  int newmask = 0x0F; // 0000...001111
  
  sum = (sum & newmask) + ((sum >> 4) & newmask) + ((sum >> 8) & newmask) + ((sum >> 12) & newmask) + ((sum >> 16) & newmask) + ((sum >> 20) & newmask) + ((sum >> 24) & newmask) + ((sum >> 28) & newmask);
  return sum;
}

int bitRepeat(int x, int n) {
   /*  */
   unsigned int slot = x;

   slot = (slot << n) | slot;
   n *= 2;
   slot = (slot << n) | slot;
   n *= 2;
   slot = (slot << n) | slot;
   n *= 2; 
   slot = (slot << n) | slot;
   n *= 2;
   slot = (slot << n) | slot;

   return slot;
 
}


int main(){
	printf("%d",bitRepeat(-559038737, 31));
}

