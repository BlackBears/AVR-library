
// global AVRLIB defines
#include "avrlibdefs.h"
// global AVRLIB types definitions
#include "avrlibtypes.h"

//#define DEBUG 1

#ifndef DUAL_USART
	#define DUAL_USART 1
#endif

#define USART_COUNT 1

#ifndef _BV
	#define _BV(bit) (1 << (bit))
#endif

#ifndef _AVR035_H_ 
#define _AVR035_H_ 

// from AVR035: Efficient C Coding for AVR 

#define SETBIT(ADDRESS,BIT) (ADDRESS |= (1<<BIT)) 
#define CLEARBIT(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT)) 
#define FLIPBIT(ADDRESS,BIT) (ADDRESS ^= (1<<BIT)) 
#define CHECKBIT(ADDRESS,BIT) ((ADDRESS) & (1<<BIT)) 

#define SETBITMASK(x,y) (x |= (y)) 
#define CLEARBITMASK(x,y) (x &= (~y)) 
#define FLIPBITMASK(x,y) (x ^= (y)) 
#define CHECKBITMASK(x,y) (x & (y)) 

#define VARFROMCOMB(x, y) x 
#define BITFROMCOMB(x, y) y 

#define C_SETBIT(comb) SETBIT(VARFROMCOMB(comb), BITFROMCOMB(comb)) 
#define C_CLEARBIT(comb) CLEARBIT(VARFROMCOMB(comb), BITFROMCOMB(comb)) 
#define C_FLIPBIT(comb) FLIPBIT(VARFROMCOMB(comb), BITFROMCOMB(comb)) 
#define C_CHECKBIT(comb) CHECKBIT(VARFROMCOMB(comb), BITFROMCOMB(comb)) 

#endif


