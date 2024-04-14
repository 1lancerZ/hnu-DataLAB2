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
 *   110
 *   101
 * ->100
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~(~x|~y);
  // ~(~x|~y) 等价于 x&y  （不知道括号能不能用...能用！）
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
  return (x>>(n<<3))&0xff;
  // n<<3即n*8
  // 要获取第n+1个字节 x右移n*8位
  // 例：getByte(0x12345678,1) = 0x56
  // 0x12345678右移1*8位 -> 0x123456
  // 这时再和0xff相与 0x123456 & 0xff
  // -> 0x56
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
  int m = 0x01;
  m = m << 31;
  m = m >> n << 1;
  return (x >> n) & (~m);
  // 逻辑移位不管左移还是右移，符号位是1还是0，都是补0
  // 可以定义一个数m
  // m的初值为0x80000000
  // m算术右移n-1位
  // 再将m按位取反后与算术右移n位的x相与
  // 得到的值的高n位都为0
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int mask1,mask2,mask3,mask4,mask5;
  mask1 = 0x55;
  mask1 = (0x55 << 8) | mask1;
  mask1 = (mask1 << 16) | mask1; //0x55555555
  mask2 = 0x33;
  mask2 = (0x33 << 8) | mask2;
  mask2 = (mask2 << 16) | mask2; //0x33333333
  mask3 = 0x0f;
  mask3 = (0x0f << 8) | mask3;
  mask3 = (mask3 << 16) | mask3; //0x0f0f0f0f
  mask4 = 0xff;
  mask4 = (0xff << 16) | mask4;  //0x00ff00ff
  mask5 = (0xff << 8) | 0xff;//0x0000ffff
  x = (x & mask1) + ((x >> 1) & mask1);
  x = (x & mask2) + ((x >> 2) & mask2);
  x = (x & mask3) + ((x >> 4) & mask3);
  x = (x & mask4) + ((x >> 8) & mask4);
  x = (x & mask5) + ((x >> 16) & mask5);
  return x;
  // 思路不说了，抄的网上的
  // 但是当x=0x7fffffff时我的输出结果为0xe
  // 我试了无数遍最后终于发现了问题所在
  // 我此处的括号没加导致运算错误 ：x = (x & mask1) + (x >> 1) & mask1;  后面四个也没加括号
  // 我、以、为、&、运、算、的、优、先、级、在、加、法、之、上、所、以、没、加、括、号、
  // 没想到居然是加法优先级更高
  // 在这个坑里卡了半天才发现……
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  return ~((x|(~x + 1)) >> 31) & 1;
  // 全为0时返回1，否则返回0
  // 对x按位取反，如果x=0时得到0xffffffff
  // 此时x+1得到0
  // 如果x!=0时按位取反得到的结果+1的最高位为1
  // 考虑到负数的符号为1，在移位之前还需要跟最初的x相或
  // 要得到最后的结果只要再取反与1就行了
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1<<31;
  // 要求返回最小的二进制补码整数，即0x80000000
  // 1左移31位即可
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
  int shift = 32 + (~n) + 1; //32-n
  return !(x ^ (x << shift >> shift));
  // 当x能被表示为n位二进制补码时返回1，n位二进制补码的范围为-2^(n-1)~2^(n-1)-1
  // x左移32-n位再右移32-n位得到的结果是x的低n位
  // 如果结果与最初的x相同的话返回1，否则返回0
  // 例：
  // fitsBits(5,3) 假设是8位，因为好演示
  // 00000101 << 5 >> 5 -> 11111101 不相同，返回0
  // fitsBits(-4,3)
  // 11111100 << 5 >> 5 -> 11111100 相同，返回1
  // 答案真错了吧 fitsBits(0x80000000,32) 真能表示吧
  // 不是32位有啥不能表示啊
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
  int sign = x >> 31; //正数全0负数全1
  int bias = (1 << n) + (~0);
  return (x + (bias & sign)) >> n;
  // 正数还能靠x>>n来算，这样算下来确实是向下取整（向零取整）的
  // 但是负数这样算的话不是向零取整，而是向下取整
  // 想你了，if
  // 负数如果想实现向零取整（向上取整）则需要加上一个值为2^n-1的偏置量（证明在《深入理解计算机系统》第三版73页）
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
  // 返回x相反数，取反+1
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  int sign = x >> 31;
  return ~(((x + (~0)) >> 31) ^ (sign)) & (!sign);
  // x>0返回1,否则返回0
  // 难点是0和0x80000000如何区分
  // -1再判断符号位是否与原符号位相等
  // 不相等的就是0和0x80000000 返回0
  // 相等的再判断原符号位是1还是0
  // 纯靠自己想出来的，无敌
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int signx = x >> 31;
  int signy = y >> 31;
  int isSame = !(signx ^ signy); //符号相同为1、不相同为0
  int sub = y + (~x) + 1;
  return (!(signy & 1 ) & (!isSame)) | (!(sub >> 31) & isSame);
  // 判断x<=y即判断y-x>=0，这我可太会了
  // 但是事情好像没那么简单，会有溢出的情况
  // 分三种情况：x正y负、x负y正、xy同号
  // x正y负 返回0
  // x负y正 返回1
  // xy同号 相减判断符号
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  int bitsNo = 0;
  bitsNo = (!!(x >> 16)) << 4;  
  bitsNo = bitsNo + ((!!(x >> (8 + bitsNo))) << 3);
  bitsNo = bitsNo + ((!!(x >> (4 + bitsNo))) << 2);
  bitsNo = bitsNo + ((!!(x >> (2 + bitsNo))) << 1);
  bitsNo = bitsNo + (!!(x >> (1 + bitsNo)));
  return bitsNo;
  // 二分法分五次求log2
  // 设定一个bitsNo，先将x右移16位看看x是否大于等于1。
  // 是(x >= 0x00010000)则令bitsNo = 16，否则另bitsNo = 0
  // 接下来继续二分，x移位相应地要加上bitsNo
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
  if((uf << 1 >> 1) > 0x7F800000){
    return uf;
  }
  else{
    return uf + 0x80000000;
  }
  // 哈哈，回来了，都回来了
  // 返回-f只要变符号位就行
  // 如果是NaN的话返回原本的值
  // NaN：s11111111xxxxxxxxxxxxxxxxxxxxxxx  后面的xxx != 0
  // 左移一位再右移移位得到低31位，判断这个值是否大于0x7F800000
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  return 2;
  // 把int型的x用浮点数表示
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  return 2;
}
