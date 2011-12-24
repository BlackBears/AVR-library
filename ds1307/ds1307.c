/*
 * ds1307.c
 *
 * Created: 12/23/2011 8:08:40 AM
 *  Author: Owner
 */ 

#include "ds1307.h"
#include "i2cmaster.h"
#include <util/delay.h>

//
//  DS1307 register addresses
//
#define DS1307_SECONDS  0x00
#define DS1307_MINUTES  0x01
#define DS1307_HOURS    0x02
#define DS1307_DAY      0x03
#define DS1307_DATE     0x04
#define DS1307_MONTH    0x05
#define DS1307_YEAR     0x06
#define DS1307_CONTROL  0x07

#define DS1307_CONTROL_OUT  (1<<7)
#define DS1307_CONTROL_SQWE (1<<4)
#define DS1307_CONTROL_RS1  (1<<1)
#define DS1307_CONTROL_RS0  (1<<0)
#define DS1307_CH	(1<<7)

#define DS1307_ADDRESS  0xD0    //  the device address

//
//  Function prototypes
//
uint8_t _ds1307_bcd_2_dec(uint8_t bcd);
void _ds1307_start_oscillator();

void ds1307_init()
{
    i2c_init();
	_ds1307_start_oscillator();
}
void ds1307_read_date(DS1307Date *date)
{
    i2c_start_wait( DS1307_ADDRESS + I2C_WRITE );
    i2c_write( DS1307_SECONDS );
    //i2c_stop();
    
    //  read registers sequentially
    i2c_rep_start( DS1307_ADDRESS + I2C_READ );
    date->second = _ds1307_bcd_2_dec( i2c_readAck() & 0x7F );
    date->minute = _ds1307_bcd_2_dec( i2c_readAck() );
    date->hour = _ds1307_bcd_2_dec( i2c_readAck() );
    date->day = _ds1307_bcd_2_dec( i2c_readAck() );
    date->date = _ds1307_bcd_2_dec( i2c_readAck() );
    date->month = _ds1307_bcd_2_dec( i2c_readAck() );
    date->year = _ds1307_bcd_2_dec( i2c_readNak() );
    
    i2c_stop();
}

void ds1307_set_military_mode()
{
	//	read the current minutes
	i2c_start_wait(DS1307_ADDRESS + I2C_WRITE);
	i2c_write( DS1307_MINUTES );
	i2c_rep_start(DS1307_ADDRESS + I2C_READ);
	unsigned char temp = i2c_readNak();
	
	temp &= 0b10111111;
	
	//	write back out
	i2c_start_wait(DS1307_ADDRESS + I2C_WRITE);
	i2c_write( DS1307_MINUTES );
	i2c_write( temp );
	i2c_stop;
}

//
//  Converts raw data from BCD to decimal
//
uint8_t _ds1307_bcd_2_dec(uint8_t bcd)
{
    uint8_t dec = 10 * (bcd>>4);
    dec += bcd & ~(0b11110000);
    return dec;
}

//
//  At power-on, the CH bit of register 0x00 is set of 1
//  preventing the oscillator from running.  Therefore, at
//  init, we clear the CH bit
//
void _ds1307_start_oscillator()
{
	//	Clear the CH bit of the register at 0x00 to
	//	enable the oscillator
	i2c_start_wait(DS1307_ADDRESS + I2C_WRITE);
	i2c_write( DS1307_SECONDS );
	i2c_rep_start(DS1307_SECONDS + I2C_READ);
	unsigned char temp = i2c_readNak();
	
	i2c_stop();
	
	temp &= 0b01111111;		//	clear the CH bit
	
	i2c_start_wait(DS1307_ADDRESS + I2C_WRITE);
	i2c_write( DS1307_SECONDS );
	i2c_write( temp );
	i2c_stop;
}