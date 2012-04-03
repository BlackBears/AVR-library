/*
 * _644_test_mcp23008_interrupt.c
 *
 * Created: 1/1/2012 3:27:56 PM
 *  Author: Owner
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "global.h"
#include "i2c.h"
#include "mcp23008.h"
#include <util/delay.h>

volatile MCP23008 gpio;
u08 data[2];

int main(void)
{
	mcp23008_init(&gpio,0b000);
	mcp23008_write_register(&gpio, MCP23008_IODIR, 0b00000000);	//	all output
	
	DDRD = 0xFF;
	for( u08 i = 0; i < 0x100; i++ )
	{
		PORTD = i;
		mcp23008_write_register(&gpio,MCP23008_GPIO,i);
		_delay_ms(50);
	}	
}
