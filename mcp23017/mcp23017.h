/************************************************************************
+																								+
|	mcp23017.h																				|
|	Title:			Interface for MCP23017 16-bit I2C port expander			|
|	Author:			Alan K. Duncan <duncan.alan@mac.com>						|
|	Software:		AVR-GCC 3.4.3 / avr-libc 1.2.3								|
|	Target:			any AVR device														|
|	Last update:	2011-12-24															|
+																								+
************************************************************************/

#ifndef MCP23017_H_
#define MCP23017_H_

#include "global.h"
#include <inttypes.h>

/************************************************************************/
/* MCP23017 REGISTER DEFINITIONS                                        */
/************************************************************************/
#define MCP23017_IODIRA 0x00
#define MCP23017_IODIRB 0x01
#define MCP23017_IPOLA 0x02
#define MCP23017_IPOLB 0x03
#define MCP23017_GPINTENA 0x04
#define MCP23017_GPINTENB 0x05
#define MCP23017_DEFVALA 0x06
#define MCP23017_DEFVALB 0x07
#define MCP23017_INTCONA 0x08
#define MCP23017_INTCONB 0x09
#define MCP23017_IOCON 0x0A
#define MCP23017_GPPUA 0x0C
#define MCP23017_GPPUB 0x0D
#define MCP23017_INTFA 0x0E
#define MCP23017_INTFB 0x0F
#define MCP23017_INTCAPA 0x10
#define MCP23017_INTCAPB 0x11
#define MCP23017_GPIOA 0x12
#define MCP23017_GPIOB 0x13
#define MCP23017_OLATA 0x14
#define MCP23017_OLATB 0x15

//	
//	MCP23017 type is used to hold the device address and the data to be
//	written to the device (or read from the device)
//
typedef struct {
	u08 address;	//	the address of the device
	u16 data;		//	data to/from device
} MCP23017;

//	
//	Initialize the device.
//	The provided address should be just the hardware component, A2-A0 (e.g. 0b000 if all are GND)
//
void mcp23017_init(MCP23017 *obj, u08 address);

//
//	Write 16 bits of data to the device with GPIOA representing the lower
//	8 bits and GPIOB the upper
//
void mcp23017_write(MCP23017 *object);

//	
//	Write to a register
//
void mcp23017_write_register( MCP23017 *obj, u08 reg, u08 data);

//	Read from a register
u08 mcp23017_read_register( MCP23017 *obj, u08 reg);

void mcp23017_write_word( MCP23017 *obj, u08 reg );

#endif /* MCP23017_H_ */