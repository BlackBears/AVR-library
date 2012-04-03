/*
 * akd_usart_2.c
 *
 * Created: 12/30/2011 6:33:02 AM
 *  Author: Owner
 */ 

#include "global.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#define BAUD 9600
#include <util/setbaud.h>

#include "akd_usart_2.h"

/** @brief  UART Baudrate Expression
 *  @param  xtalcpu  system clock in Mhz, e.g. 4000000L for 4Mhz          
 *  @param  baudrate baudrate in bps, e.g. 1200, 2400, 9600     
 */
#define UART_BAUD_SELECT(baudRate,xtalCpu) ((xtalCpu)/((baudRate)*16l)-1)

/* Initialize UART */

void usart2_init_baudrate(u08 usart, u32 baudrate)
{
	u16 baudval = UART_BAUD_SELECT(baudrate,F_CPU);
	usart2_init_baudvalue(usart,baudval);
}

void usart2_init_baudvalue(u08 usart, u16 baudval)
{
	if( usart ) {
		//	set baud rate for usart1
		UBRR1H = (u08)(baudval>>8);
		UBRR1L = (u08)baudval;
		
		/* Enable UART receiver and transmitter */
		UCSR1B = ( ( 1 << RXEN1 ) | ( 1 << TXEN1 ) ); 
		/* Set frame format: 8 data 2stop */
		UCSR1C = (1<<USBS1)|(1<<UCSZ11)|(1<<UCSZ10); 
	}
	else
	{
		//	set baud rate for usart0
		UBRR0H = (u08)(baudval>>8);
		UBRR0L = (u08)baudval;
		
		/* Enable UART receiver and transmitter */
		UCSR0B = ( ( 1 << RXEN0 ) | ( 1 << TXEN0 ) ); 
		
		/* Set frame format: 8 data 2stop */
		UCSR0C = (1<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00); 
	}
}

void usart2_transmit( u08 usart, u08 data)
{
	if( usart ) {
		/* Wait for empty transmit buffer */
		while ( !(UCSR1A & (1<<UDRE1)) )
			; 			                
		/* Start transmission */
		UDR1 = data;
	}
	else {
		/* Wait for empty transmit buffer */
		while ( !(UCSR0A & (1<<UDRE0)) )
			; 			                
		/* Start transmission */
		UDR0 = data;
	}
}

u08 usart2_receive(u08 usart) {
	if( usart ) {
		/* Wait for incoming data */
		while ( !(UCSR1A & (1<<RXC1)) ) 	
			;			                
		/* Return the data */
		return UDR1;
	}
	else {
		/* Wait for incoming data */
		while ( !(UCSR0A & (1<<RXC0)) ) 	
			;			                
		/* Return the data */
		return UDR0;
	}
}

void usart2_puts( u08 usart, const char *s)
{
	while( *s )
		usart2_transmit(usart,*s++);
}


/*************************************************************************
Function: uart2_puts_p()
Purpose:  transmit string from program memory to UART1
Input:    program memory string to be transmitted
Returns:  none
**************************************************************************/
void uart2_puts_p(u08 usart, const char *progmem_s )
{
    register char c;
    
    while ( (c = pgm_read_byte(progmem_s++)) ) 
      usart2_transmit(usart, c);

}/* uart1_puts_p */