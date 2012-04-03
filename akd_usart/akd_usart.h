/*
 * akd_usart.h
 *
 * Created: 1/1/2012 1:28:58 PM
 *  Author: Owner
 */ 


#ifndef AKD_USART_H_
#define AKD_USART_H_

#include "global.h"

#if DUAL_USART
#warning *** DO NOT USE akd_usart if there is only a single USART module ***
#endif

void usart_init_baudrate(u32 baudrate);
void usart_init_baudvalue(u16 baudval);
void usart_transmit( u08 data);
u08 usart_receive();
void usart_puts( const char *s);
void uart_puts_p(const char *progmem_s );



#endif /* AKD_USART_H_ */