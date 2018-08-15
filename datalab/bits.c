/* 
 * CS:APP Data Lab 
 * 
 * Konner Macias | 004603916
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  /* this shifts x so that the sign bit covers all 32 bits.
     So it's either all 1s or 0s. Then on the right side of |
     we have it be all zeroes if x is zero and all ones o/w.
     Adding one at the end will transform the all ones to 0, 
     and the all zeroes to 1 thus simulating bang!
  */
  return ((x >> 31) | ((~x+1) >> 31)) + 1;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  /* This is a good one. So we first must create a mask of 00010001
     repeat to help us compute the number of 1 bits within our first
     four bits. Then we use the variable newmask and by continually
     shifting by 4 and &-ing to help determine our final sum! */

  int halfmask = 0x11 | (0x11 << 8);
  int fullmask = halfmask | (halfmask << 16);
  int newmask = 0xF;
  
  int sum = (x & fullmask);
  sum = sum + (fullmask & (x >> 1));
  sum = sum + (fullmask & (x >> 2));
  sum = sum + (fullmask & (x >> 3));
  
  
  sum = (sum & newmask) + ((sum >> 4) & newmask) + ((sum >> 8) & newmask) + ((sum >> 12) & newmask) + ((sum >> 16) & newmask) + ((sum >> 20) & newmask) + ((sum >> 24) & newmask) + ((sum >> 28) & newmask);
  return sum;
}
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
  /* exploits DeMorgan's law */
  return ~(~x & ~y); 
}
/*
 * bitRepeat - repeat x's low-order n bits until word is full.
 *   Can assume that 1 <= n <= 32.
 *   Examples: bitRepeat(1, 1) = -1
 *             bitRepeat(7, 4) = 0x77777777
 *             bitRepeat(0x13f, 8) = 0x3f3f3f3f
 *             bitRepeat(0xfffe02, 9) = 0x10080402
 *             bitRepeat(-559038737, 31) = -559038737
 *             bitRepeat(-559038737, 32) = -559038737
 *   Legal ops: int and unsigned ! ~ & ^ | + - * / % << >>
 *             (This is more general than the usual integer coding rules.)
 *   Max ops: 40
 *   Rating: 4
 */
int bitRepeat(int x, int n) {
  /* In order to return the desired repeated bit pattern, we must
     isolate the our bit pattern which allows us to create a mask. By shifting and |ing by larger intervals each time, we can return the desired output.  */ 

    unsigned int temp = (x << (32 - n));
    unsigned int mask = temp >> (32 - n);
    
    int n2 = n*2;
    int n4 = n*4;
    int n8 = n*8;
    int n16 = n*16;
    
    int x1 = !(n/32);
    int x2 = !(n2/32);
    int x4 = !(n4/32);
    int x8 = !(n8/32);
    int x16 = !(n16/32);
    
    mask = (mask << (n*x1)) | (mask*(x1));
    mask = (mask << (n2*x2)) | (mask*(x2));
    mask = (mask << (n4*x4)) | (mask*(x4));
    mask = (mask << (n8*x8)) | (mask*(x8));
    mask = (mask << (n16*x16)) | (mask*(x16));
    
    return mask;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  /* First, we find a shift amount based on number of bits. 
     Then, we shift back and forth. This is a way of making sure 
     the 1 bits will "fall off" if there is no room. Then we use ^
     to check for any differences. If they are the same, then it 
     fits bits!
 */
  int a = (33 + (~n)); 
  int b = (x << a); 
  int c = (b >> a); 
  return !(c^x); 
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 
 */
int getByte(int x, int n) {
  /* 0xFF is used as a mask so that the last 8 bits are 1s. 
     We then shift x based on n so that the remaining 8 bits
     are the corresponding bits we'd like to extract. The mask 
     works to select that last byte. */
  return 0xFF & (x >> (n << 3));
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */  
int isLessOrEqual(int x, int y) {
  /* to check if x <=y, I looked at if y-x >= 0. First, I looked at 
     whether the signs were different. Then i checked if x and y had
     different signs and whether x is negative. This tells me of 
     course x is less or equal to y! I also checked if they
     had the same sign and if y-x is positive or zero. By exploiting 
     |, I was able to check both sides!*/
  int diff = !(x>>31)^!(y>>31);
  int diff_and_xneg = diff & (x>>31);        
  int same_and_pos = !diff & !((y+(~x+1))>>31); 
  int k = diff_and_xneg | same_and_pos;
  
  return k;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  /* We first get whether the sign bit of x is +/- through a mask 
     with tmin. Then we must check the case where it's zero so we 
     use xor to check if there's difference there. */
  int sign = !((1 << 31) & x);
  int zero = !x;
  return sign ^ zero;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  /* Our goal is to create a mask where n bits on the lefthand side 
     are zeroes. By shifting tmin by n and accounting for the extra 1
     we can achieve our goal by inverting our mask and &-ing with the 
     shifted x by n thus creating our logical shift!*/
  int mask = ((1 << 31) >> n) << 1;
  return (x >> n) & ~mask;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  /* 1 shifted 31 spots gives 100...00. which is tmin */
  return (1 << 31);
}
