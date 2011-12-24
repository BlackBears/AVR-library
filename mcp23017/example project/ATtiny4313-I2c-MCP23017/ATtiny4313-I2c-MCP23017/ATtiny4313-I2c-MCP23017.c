/*
 * ATtiny4313_I2c_MCP23017.c
 *
 * Created: 12/23/2011 8:05:37 PM
 *  Author: Owner
 */ 

#include "global.h"
#include <util/delay.h>
#include <avr/io.h>
#include <mcp23017.h>
#include "i2cmaster.h"

MCP23017 device;
u08 data;

int main(void)
{
	mcp23017_init(&device, 0b000);
	
	while(1)
	{
		mcp23017_write(&device);
		device.data++;
		if( device.data == 0xFF)
			device.data = 0x00;
		_delay_ms(50);
	}
}