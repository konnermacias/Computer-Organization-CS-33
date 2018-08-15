// compiled with gcc -O2 -S cread_alt.c

long cread_alt(long *xp){
	long temp = 0;
	if (*xp > 0){
		temp = *xp;
	}
	return temp;
}

