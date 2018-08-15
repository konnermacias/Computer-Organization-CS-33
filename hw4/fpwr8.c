// Konner Macias | 004603916
// 8^x instead of 2^x
// 8^x is equivalent to 2^3x

static float u2f(unsigned u){
	/* union has the property that only one member may contain a value. All variables share memory */
	union {
    		unsigned u;
    		float f;
  	} v;
  	v.u = u;
  	return v.f;
}

float fpwr8(int x){
	
	unsigned exp, frac;
	unsigned u;

	if (x < -49){
		/* too small. return 0.0 */
		exp = 0;
		frac = 0;
	} else if (x < -42){
		/* Denormalized result */
		exp = 0;
		frac = 1 << (3*x + 149);
	} else if (x < 43){
		/* Normalized result */
		exp = 3*x + 127;
		frac = 0;
	} else {
		/* too big. Return +oo */
		exp = 255;
		frac = 0;
	}
	
	u = exp << 23 | frac;
	return u2f(u);
} 
