/*
 * akd_usart_2.h
 *
 * Created: 12/30/2011 7:46:33 AM
 *  Author: Owner
 */ 


#ifndef AKD_USART_2_H_
#define AKD_USART_2_H_

#include "global.h"

void usart2_init_baudrate(u08 usart, u32 baudrate);
void usart2_init_baudvalue(u08 usart, u16 baudval);
void usart2_transmit( u08 usart, u08 data);
u08 usart2_receive(u08 usart);
void usart2_puts( u08 usart, const char *s);
void uart2_puts_p(u08 usart, const char *progmem_s );

#endif /* AKD_USART_2_H_ */