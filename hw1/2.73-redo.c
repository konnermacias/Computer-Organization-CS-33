#include <stdio.h>
#include <limits.h>

int saturating_add(int x, int y){

	int sum = x + y;
	int posOverflow = (~x & ~y & sum); // Sign bit will be negative if there is positive or negative overflow
	long overflow = __builtin_add_overflow_p(x,y,(int)0);
	int negOverflow = (x & y & ~sum);
	
	// For the sake of our return statement, make all the bits 1 if it overflowed, 0 if not.
	posOverflow = posOverflow >> (sizeof(int) << 3) - 1;
	negOverflow = negOverflow >> (sizeof(int) << 3) - 1;
	overflow = ~(overflow - 1) >> (sizeof(int) << 3) - 1;

	// Convenient way of checking for overflows, and spitting out the desired answer
	return ((((posOverflow & INT_MAX) + (negOverflow & INT_MIN)))&overflow) + (((~posOverflow) & (~negOverflow)) & sum);
}

int main(void){
	printf("%d", saturating_add(INT_MAX, 1));
	return 0;
}
