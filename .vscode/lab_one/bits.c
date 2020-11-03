/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~(~x|~y);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2	
 */
int getByte(int x, int n) {
	//>>for n Bytes then get the last Byte
	x=x>>(n<<3);
  return x&0xff;
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
	int tool=((1<<31)>>n)<<1;//have n 1 in the left
	tool=~tool;//n 0 in the left and 1 for the remains
  return (x>>n)&tool;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  //get the count of 1, an 1 may be pow(2,n) in origin
  //for x=11, we could count (x>>1)&01 for the first 1 and x&01 for the second
  //add them, then get the number of 1 in "11", repeat it until we get the ans
  int model0101=(0x55)|(0x55<<8);
  model0101=model0101|(model0101<<16);//01 01 01 01 ...
  int count=(x&model0101)+((x>>1)&model0101);//for every two bits, we turns 01 and 10->01, 11->10
  
  int model0011=(0x33)|(0x33<<8);
  model0011=(model0011)|(model0011<<16);//0011 0011 0011 0011 ...
  count=(count&model0011)+((count>>2)&model0011);//max 4_0100 in every group
  
  int model4s0_4s1=(0x0f)|(0x0f<<8);
  model4s0_4s1=(model4s0_4s1)|(model4s0_4s1<<16);//00001111 00001111 ...
  count=(count+(count>>4))&model4s0_4s1;//max result 8(4bits) won't exceed half of the model(4bits), thus no need for &twice
  
  int model8s0_8s1=(0xff)|(0xff<<16);
  count=(count+(count>>8))&model8s0_8s1;//max result 16(5bits) won't exceed half of the model(8bits)
  
  int model16s0_16s1=(0xff)|(0xff<<8);
  count=(count+(count>>16))&model16s0_16s1;//max result 32(6bits) won't exceed half of the model(16bits)
  
  return count;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  int minusX=~x+1;
  int result=minusX|x;//if x>0, minusX<0, result have 1 at first bit; if x=0, minusX=0, result have 0 at first bit
  return (result>>31)+1;//0xffffffff+1=0;0+1=1;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1<<31;
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
  int shift=32+(~n+1);//移动的长度，32-n位.左移消除了多于n位的信息，如果不需多于n位即可表示，消除后不会改变数值
  return !(x^((x<<shift)>>shift));
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
//正数情况下，直接右移即可，结果将向下取整。但负数情况下，期望做到的是向上取整
//利用(x/y)向上取整=(x+y-1/y)向下取整，当x＜0时，先加上2^n-1再右移即可
    int bias = (1 << n) + (~0);//得到2^n - 1
    bias = (x>>31) & bias;//x为正时不施加偏移
    return (x + bias) >> n;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return (~x)+1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
//x>>31将最高位拓展，正数为0负数为1，+1后，>=0为1而<0为0
//但是，0的输入也要被排除，应而并上!(!x)，必须非零才能导出1
  return ((x>>31)+1)&!(!x);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
//分3类：x<0且y>=0；x和y同号，避免溢出地获取x-y,看是否为负；x和y是否相等
  //1
  int signX=(x>>31)&1;
  int signY=(y>>31)&1;
  int signDiff=(signX^signY)&signX;//异号且x为负
  //2
  int signSame=((x+(~y)+1)>>31&1)&(!(signX^signY));//同号且相减为负
  //3
  int isSame=!(x^y);
  return signDiff|signSame|isSame;
  
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
//右移n位后为0，说明小于等于n，否则大于n
//以16、8、4、2、1为n二分迭代
  int count=(!!(x>>16))<<4;
  count=(!!(x>>16))<<4;//右移16，为0说明低于16位，进入下次迭代；为1说明高于16，加16进入下次迭代
  count=count+((!!(x>>(count+8)))<<3);
  count=count+((!!(x>>(count+4)))<<2);
  count=count+((!!(x>>(count+2)))<<1);
  count=count+(!!(x>>(count+1)));
  return count;
}
