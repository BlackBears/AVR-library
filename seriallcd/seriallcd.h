/*
 * seriallcd.h
 *
 * Created: 12/26/2011 9:10:34 PM
 *  Author: Owner
 */ 


#ifndef SERIALLCD_H_
#define SERIALLCD_H_

#include "global.h"

enum {
	CursorTypeUnderline,
	CursorTypeBox,
};
typedef u08 CursorType;

void serial_lcd_init();
void serial_lcd_clear_screen(void);
void serial_lcd_set_line( u08 line);
void serial_lcd_set_backlight( BOOL isON);
void serial_lcd_set_position( u08 row, u08 col);
void serial_lcd_write_string( char *str );
void serial_lcd_set_cursor_type_state(CursorType type, BOOL state);

#endif /* SERIALLCD_H_ */