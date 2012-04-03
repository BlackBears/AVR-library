/*
 * seriallcd.h
 *
 * Created: 12/26/2011 9:10:34 PM
 *  Author: Owner
 */ 


#ifndef SERIALLCD_H_
#define SERIALLCD_H_

#include "global.h"

typedef enum {
	SerialLCDUARTSingle = 0xFE,
	SerialLCDUART0 = 0,
	SerialLCDUART1
} SerialLCDUART;

typedef struct {
	SerialLCDUART uart;
	u32 baudrate;
} SerialLCD;

enum {
	CursorTypeUnderline,
	CursorTypeBox,
};
typedef u08 CursorType;

void serial_lcd_init(SerialLCD *lcd);
void serial_lcd_clear_screen(SerialLCD *lcd);
void serial_lcd_set_line( SerialLCD *lcd, u08 line);
void serial_lcd_set_backlight( SerialLCD *lcd, BOOL isON);
void serial_lcd_set_position( SerialLCD *lcd, u08 row, u08 col);
void serial_lcd_write_string( SerialLCD *lcd, char *str );
void serial_lcd_write_byte( SerialLCD *lcd, char data );
void serial_lcd_set_cursor_type_state(SerialLCD *lcd, CursorType type, BOOL state);

#endif /* SERIALLCD_H_ */