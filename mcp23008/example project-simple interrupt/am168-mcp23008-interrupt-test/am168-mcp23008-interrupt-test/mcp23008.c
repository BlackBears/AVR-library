/*
 * mcp23008.c
 *
 * Created: 12/29/2011 3:24:48 PM
 *  Author: Owner
 */ 

#include "mcp23008.h"
#include "global.h"
#include "i2c.h"

#define MCP23008_BASE_ADDRESS	0x40

u08 mcp23008_data[2];

void mcp23008_init(MCP23008 *obj, u08 address)
{
	i2cInit();
	obj->address = MCP23008_BASE_ADDRESS + address;
}

void mcp23008_write(MCP23008 *object)
{
	mcp23008_write_register(object,MCP23008_GPIO,object->data);
}

void mcp23008_write_register( MCP23008 *obj, u08 reg, u08 data)
{
	mcp23008_data[0] = reg;
	mcp23008_data[1] = data;
	i2cMasterSendNI(obj->address,2,&mcp23008_data);
}

u08 mcp23008_read_register( MCP23008 *obj, u08 reg)
{
	mcp23008_data[0] = reg;
	i2cMasterSendNI(obj->address,1,&mcp23008_data);
	i2cMasterReceiveNI(obj->address,1,&mcp23008_data);
	return mcp23008_data[0];
}