/************************************************************************/
/* MCP23008 INTERRUPT TEST                                              */
/************************************************************************/

/*
 *	Of the three MCP23008 test cases, this is the most complex			*
 *	In this case, we are using INT1 for the MCP23008 interrupt			*
 *	signal; so we connect the MCP23008 INT output to the INT1 pin on	*
 *	the AVR.  To simulate external changes on the MCP23008 we use		*
 *	PD6 attached to one of the GPIO pins on the MCP23008.  Every 2 secs *
 *	we drive PD6 low for 10 ms to generate a change on the MCP23008.	*
 *	When this differs from the expect DEFVAL, it triggers an interrupt	*
 *	and the AVR flashes an LED.											*
 */

//////////////////////////////////////////////////////////////////////////
//	Physical setup on ATmega 168 and MCP23008
//
//	MCP23008 INT -> PD3 (INT1)
//	MCP23008 GPIO7 -> PD6
//	PD5 -> an LED (use an activity indicator for testing)
//	All of the address lines on MCP23008 should be connected to GND
//	SDA and SCL should be pulled up with 4K7 resistors
//
//////////////////////////////////////////////////////////////////////////

#include <avr/io.h>
#include <avr/interrupt.h>
#include "global.h"
#include "i2c.h"
#include "mcp23008.h"
#include <util/delay.h>

volatile MCP23008 gpio;
u08 data[2];

void _flash();

int main(void)
{
	DDRD |= (1<<PD5) | (1<<PD6);
	PORTD |= (1<<PD5) | (1<<PD6);
	
	_flash();	// show that we're alive
	_delay_ms(1000);	// wait then start
	
	mcp23008_init(&gpio,0b000);
	
	mcp23008_write_register(&gpio, MCP23008_IODIR, 0x80);	//	all pins on the MCP23008 are input
	mcp23008_write_register(&gpio,MCP23008_IPOL,0x00);		//	input polarity
	mcp23008_write_register(&gpio, MCP23008_GPINTEN, 0x80);	//	GPIO7 enabled for interrupt
	mcp23008_write_register(&gpio, MCP23008_INTCON, 0x80);	//	interrupt if pin differs from DEFVAL
	mcp23008_write_register(&gpio, MCP23008_DEFVAL, 0x80);	//	values other than 1 on GPIO7 trigger interrupt
	mcp23008_write_register(&gpio, MCP23008_IOCON, 0b00101000);
	
	mcp23008_write_register(&gpio,MCP23008_GPPU, 0x01);
	
	//	install interrupt INT1
	EICRA |= (1<<ISC11);	//	falling edge on INT1 triggers interrupt
	EIMSK |= (1<<INT1);		//	enable INT1
	sei();
	
	u08 temp = mcp23008_read_register(&gpio,MCP23008_GPIO);
	for(;;) {
		//	every 2 seconds, drive PD6 low for 10 ms
		PORTD &= ~(1<<PD6);
		_delay_ms(50);
		PORTD |= (1<<PD6);
		
		//	read to clear the interrupt (IMPORTANT)
		//	we are reading here because this is the last point where the condition
		//	generating the interrupt is still present.  With a purely externally
		//	triggered interrupt, this would not be necessary.
		u08 temp = mcp23008_read_register(&gpio,MCP23008_GPIO);		
		
		//	wait a little
		_delay_ms(2000);
		
	}
}

ISR(INT1_vect) {
	//	flash to indicate activity
	_flash();	
	//	read to clear the interrupt (IMPORTANT)
	u08 temp = mcp23008_read_register(&gpio,MCP23008_GPIO);
	
}

void _flash()
{
	for( u08 i = 0; i < 6; i++) {
		PORTD ^= (1<<PD5);
		_delay_ms(50);
	}
}
