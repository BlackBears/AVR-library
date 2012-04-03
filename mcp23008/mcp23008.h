/*
 * mcp23008.h
 *
 * Created: 12/29/2011 3:25:00 PM
 *  Author: Owner
 */ 


#ifndef MCP23008_H_
#define MCP23008_H_

#include "global.h"
#include <inttypes.h>

/************************************************************************/
/* REGISTER DEFINITIONS                                                 */
/************************************************************************/
#define MCP23008_IODIR		0x00
#define MCP23008_IOPOL		0x01
#define MCP23008_GPINTEN	0x02
#define MCP23008_DEFVAL		0x03
#define MCP23008_INTCON		0x04
#define MCP23008_IOCON		0x05
#define MCP23008_GPPU		0x06
#define MCP23008_INTF		0x07
#define MCP23008_INTCAP		0x08
#define MCP23008_GPIO		0x09
#define MCP23008_OLAT		0x0A 

typedef struct {
	u08 address;
	u08 data;
} MCP23008;


//	
//	Initialize the device.
//	The provided address should be just the hardware component, A2-A0 (e.g. 0b000 if all are GND)
//
void mcp23008_init(MCP23008 *obj, u08 address);

//
//	Write 8 bits of data to the device GPIO
//
void mcp23008_write(MCP23008 *object);

//	
//	Write to a register
//
void mcp23008_write_register( MCP23008 *obj, u08 reg, u08 data);

//	Read from a register
u08 mcp23008_read_register( MCP23008 *obj, u08 reg);

#endif /* MCP23008_H_ */