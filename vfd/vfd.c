#include "vfd.h"
#include <util/delay.h>

enum {
    VFD_WRITE_COMMAND,
    VFD_WRITE_DATA
};
typedef uint8_t command_or_data;

#define vfd_cs_low() VFD_CS_PORT &= ~_BV(VFD_CS_PIN)
#define vfd_cs_high() VFD_CS_PORT |= _BV(VFD_CS_PIN)
#define vfd_wr_low() VFD_WR_PORT &= ~_BV(VFD_WR_PIN)
#define vfd_wr_high() VFD_WR_PORT |= _BV(VFD_WR_PIN)
#define vfd_a0_low()  VFD_A0_PORT &= ~_BV(VFD_A0_PIN)
#define vfd_a0_high() VFD_A0_PORT |= _BV(VFD_A0_PIN)

/* 
** constants/macros 
*/
#define DDR(x) (*(&x - 1))      /* address of data direction register of port x */
#if defined(__AVR_ATmega64__) || defined(__AVR_ATmega128__)
    /* on ATmega64/128 PINF is on port 0x00 and not 0x60 */
    #define PIN(x) ( &PORTF==&(x) ? _SFR_IO8(0x00) : (*(&x - 2)) )
#else
	#define PIN(x) (*(&x - 2))    /* address of input register of port x          */
#endif

void _vfd_write(uint8_t data, command_or_data cmd);

void vfd_init(void)
{
    if( &VFD_DATA0_PORT == &VFD_DATA1_PORT &&
        &VFD_DATA1_PORT == &VFD_DATA2_PORT &&
        &VFD_DATA2_PORT == &VFD_DATA3_PORT &&
        &VFD_DATA3_PORT == &VFD_DATA4_PORT &&
        &VFD_DATA4_PORT == &VFD_DATA5_PORT &&
        &VFD_DATA5_PORT == &VFD_DATA6_PORT &&
        &VFD_DATA6_PORT == &VFD_DATA7_PORT )
    {
        /*  if our data is all on the same port, save time by just setting
         *  all out. */
         DDR(VFD_DATA0_PORT) = 0b11111111;
         
    }
    else
    {
        DDR(VFD_DATA0_PORT) |= _BV(VFD_DATA0_PIN);
        DDR(VFD_DATA1_PORT) |= _BV(VFD_DATA1_PIN);
        DDR(VFD_DATA2_PORT) |= _BV(VFD_DATA2_PIN);
        DDR(VFD_DATA3_PORT) |= _BV(VFD_DATA3_PIN);
        DDR(VFD_DATA4_PORT) |= _BV(VFD_DATA4_PIN);
        DDR(VFD_DATA5_PORT) |= _BV(VFD_DATA5_PIN);
        DDR(VFD_DATA6_PORT) |= _BV(VFD_DATA6_PIN);
        DDR(VFD_DATA7_PORT) |= _BV(VFD_DATA7_PIN);
    }
    /*  Set our control pin direction registers */
    DDR(VFD_WR_PORT) |= _BV(VFD_WR_PIN);
    DDR(VFD_A0_PORT) |= _BV(VFD_A0_PIN);
    DDR(VFD_CS_PORT) |= _BV(VFD_CS_PIN);
    
    /*  Set busy pin */
    DDR(VFD_BUSY_PORT) &= ~_BV(VFD_BUSY_PIN);
    
    /*  Setup initial line states */
    vfd_cs_high();
    vfd_wr_high();
    vfd_a0_high();
}

void vfd_set_luminance(LuminanceLevel luminance)
{
    _vfd_write(luminance,VFD_WRITE_DATA);
}

void vfd_cls(void)
{
    _vfd_write(VFD_CTL_CLS,VFD_WRITE_DATA);
}

void vfd_cr(void)
{
    _vfd_write(VFD_CTL_CR,VFD_WRITE_DATA);
}

void vfd_putc(char c)
{
    if( c == '\n' )
        _vfd_write(VFD_CTL_CR,VFD_WRITE_DATA);
    else
        _vfd_write(c,VFD_WRITE_DATA);
}

void vfd_puts(const char *s)
{
    register char c;
    while ( (c = *s++) ) {
        vfd_putc(c);
    }
}

void _vfd_write(uint8_t data, command_or_data cmd)
{   
    vfd_cs_low();
    if( cmd == VFD_WRITE_COMMAND )
        vfd_a0_high();
    else
        vfd_a0_low();

    if( &VFD_DATA0_PORT == &VFD_DATA1_PORT &&
        &VFD_DATA1_PORT == &VFD_DATA2_PORT &&
        &VFD_DATA2_PORT == &VFD_DATA3_PORT &&
        &VFD_DATA3_PORT == &VFD_DATA4_PORT &&
        &VFD_DATA4_PORT == &VFD_DATA5_PORT &&
        &VFD_DATA5_PORT == &VFD_DATA6_PORT &&
        &VFD_DATA6_PORT == &VFD_DATA7_PORT )
    {
        VFD_DATA0_PORT = data;
    }
    else
    {
        if( data & 0b00000001 ) VFD_DATA0_PORT |= _BV(VFD_DATA0_PIN);
        if( data & 0b00000010 ) VFD_DATA1_PORT |= _BV(VFD_DATA1_PIN);
        if( data & 0b00000100 ) VFD_DATA2_PORT |= _BV(VFD_DATA2_PIN);
        if( data & 0b00001000 ) VFD_DATA3_PORT |= _BV(VFD_DATA3_PIN);
        if( data & 0b00010000 ) VFD_DATA4_PORT |= _BV(VFD_DATA3_PIN);
        if( data & 0b00100000 ) VFD_DATA5_PORT |= _BV(VFD_DATA5_PIN);
        if( data & 0b01000000 ) VFD_DATA6_PORT |= _BV(VFD_DATA6_PIN);
        if( data & 0b10000000 ) VFD_DATA7_PORT |= _BV(VFD_DATA7_PIN);
    }
    /*  wait for BUSY line to go low */
    while( !(PIN(VFD_BUSY_PORT) & VFD_BUSY_PIN ) ) {}

    /*  strobe the *WR line */
    vfd_wr_low();
    _delay_ms(1);
    vfd_wr_high();
}

