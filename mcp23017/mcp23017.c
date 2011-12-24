/*
 * mcp23017.c
 *
 * Created: 12/23/2011 5:40:33 PM
 *  Author: Owner
 */ 

#include "mcp23017.h"
#include "i2cmaster.h"
#include <util/delay.h>

#define MCP23017_BASE_ADDRESS 0x40

void mcp23017_init(MCP23017 *obj, uint8_t address)
{
	obj->address = MCP23017_BASE_ADDRESS + address;
	
	//	set addressing style
	mcp23017_write_register(obj,MCP23017_IOCON,0x00);
	
	obj->data = 0x0000;
	mcp23017_write_word(obj,MCP23017_IODIRA);	//	make all output
}
void mcp23017_write(MCP23017 *obj)
{
	mcp23017_write_word(obj,MCP23017_GPIOA);
}

void mcp23017_write_register( MCP23017 *obj, u08 reg, u08 data)
{
	i2c_start_wait(obj->address + I2C_WRITE);
	i2c_write(reg);
	i2c_write(data);
	i2c_stop();
}

u08 mcp23017_read_register( MCP23017 *obj,u08 reg)
{
	i2c_start_wait(obj->address + I2C_WRITE);
	i2c_write( reg );
	i2c_rep_start( obj->address + I2C_READ);
	u08 data = i2c_readNak();
	i2c_stop();
	return data;
}

void mcp23017_write_word( MCP23017 *obj, u08 reg )
{
	i2c_start_wait(obj->address + I2C_WRITE);
	i2c_write(reg);
	u16 data = obj->data;		//	access our object's 16 bits of data
	i2c_write((u08)data);		//	cast and write the lower byte
	i2c_write((u08)(data>>8));	//	automatically adv address pointer and write upper
	i2c_stop();
}