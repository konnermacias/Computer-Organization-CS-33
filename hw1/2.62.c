#include <stdio.h>
int shifts_are_arithmetic(void)
{
	int i = ~0;
	int j = i>> 1;
	return (j == i);
}


int main(void){
	printf("%d",shifts_are_arithmetic());
}
