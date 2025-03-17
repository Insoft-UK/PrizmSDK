#ifndef _MISC_H_
#define _MISC_H_

#include <stddef.h>

typedef struct BCDinternal {
  int exponent;
  int sign;
  int unknown;
  char mantissa[15];
} TBCDinternal;

typedef struct BCDbyte {
  unsigned char hnibble:4;
  unsigned char lnibble:4;
} TBCDbyte;

typedef struct BCDvalue {
  unsigned short exponent:12;
  unsigned short mantissa0:4;
  TBCDbyte mantissa[7];
  char flags;
  short info;
} TBCDvalue;
    
#ifdef __cplusplus
extern "C" {
#endif

// Don't know of anybody using these
// gbl08ma: but I do know, at least itoa is widely used. And since they're syscalls, their headers should be defined somewhere. Keeping this here.
int ItoA_10digit( int, void* );
void ByteToHex( unsigned char value, unsigned char*result );
void HexToByte( unsigned char*value, unsigned char*result );
void HexToNibble( unsigned char value, unsigned char*result );
void HexToWord( unsigned char*value, unsigned short*result );
void itoa( int value, unsigned char*result );
void LongToAscHex( int, unsigned char*, int );
void NibbleToHex( unsigned char value, unsigned char*result );
void WordToHex( unsigned short value, unsigned char*result );
int BCDtoInternal(TBCDinternal *target, TBCDvalue *source);
#endif

#ifdef __cplusplus
}
#endif
