/*
 * akd_usart.c
 *
 * Created: 1/1/2012 1:28:34 PM
 *  Author: Owner
 */ 


#include "global.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#define BAUD 9600
#include <util/setbaud.h>

#include "akd_usart.h"

/** @brief  UART Baudrate Expression
 *  @param  xtalcpu  system clock in Mhz, e.g. 4000000L for 4Mhz          
 *  @param  baudrate baudrate in bps, e.g. 1200, 2400, 9600     
 */
#define UART_BAUD_SELECT(baudRate,xtalCpu) ((xtalCpu)/((baudRate)*16l)-1)

/* Initialize UART */

void usart_init_baudrate(u32 baudrate)
{
	u16 baudval = UART_BAUD_SELECT(baudrate,F_CPU);
	usart_init_baudvalue(baudval);
}

void usart_init_baudvalue(u16 baudval)
{
	//	set baud rate for usart1
	UBRRH = (u08)(baudval>>8);
	UBRRL = (u08)baudval;
		
	/* Enable UART receiver and transmitter */
	UCSRB = ( ( 1 << RXEN ) | ( 1 << TXEN ) ); 
	/* Set frame format: 8 data 2stop */
	UCSRC = (1<<USBS)|(1<<UCSZ1)|(1<<UCSZ1); 
}

void usart_transmit( u08 data)
{
	while ( !(UCSRA & (1<<UDR1)) )
		; 			                
	/* Start transmission */
	UDR = data;
}

u08 usart_receive() {
	/* Wait for incoming data */
	while ( !(UCSR1A & (1<<RXC1)) ) 	
		;			                
	/* Return the data */
	return UDR1;
}

void usart_puts( const char *s)
{
	while( *s )
		usart2_transmit(*s++);
}


/*************************************************************************
Function: uart_puts_p()
Purpose:  transmit string from program memory to UART1
Input:    program memory string to be transmitted
Returns:  none
**************************************************************************/
void uart_puts_p(const char *progmem_s )
{
    register char c;
    
    while ( (c = pgm_read_byte(progmem_s++)) ) 
      usart2_transmit(c);

}/* uart_puts_p */