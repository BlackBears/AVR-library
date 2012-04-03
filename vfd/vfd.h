/*!	file vfd.h	brief	Vacuum fluorescent display driver for FC20x2JA-AB. */
//*****************************************************************************
//	File Name	:	'vfd.h'
//	Title		:	Vaccum fluorescent display driver for FC20x2JA-AB
//	Author		:	Alan Duncan - Copyright (c) 2012
//	Created		:	04/03/2012
//	Revised		:
//	Version		:	1.0
//	Target MCU	:	ATMEL AVR Series
//
///	\par Overview
///		This is a VFD driver for AVR-series processors.  It is specifically
///		designed to control a NEC FC20x2JA-AB 20x2 display; but may work with
///		other displays.
///
///
//*****************************************************************************

#include <avr/io.h>

#define VFD_LINES           2
#define VFD_DISP_LENGTH     20
#define VFD_PORT            PORTE
#define VFD_DATA0_PORT      VFD_PORT
#define VFD_DATA1_PORT      VFD_PORT
#define VFD_DATA2_PORT      VFD_PORT
#define VFD_DATA3_PORT      VFD_PORT
#define VFD_DATA4_PORT      VFD_PORT
#define VFD_DATA5_PORT      VFD_PORT
#define VFD_DATA6_PORT      VFD_PORT
#define VFD_DATA7_PORT      VFD_PORT

#define VFD_DATA0_PIN		0
#define VFD_DATA1_PIN		1
#define VFD_DATA2_PIN		2
#define VFD_DATA3_PIN		3
#define VFD_DATA4_PIN		4
#define VFD_DATA5_PIN		5
#define VFD_DATA6_PIN		6
#define VFD_DATA7_PIN		7


/*      CONTROL PORTS/PINS */
#define VFD_CTL_PORT        PORTD
#define VFD_CS_PORT			VFD_CTL_PORT
#define VFD_CS_PIN			2
#define VFD_A0_PORT			VFD_CTL_PORT
#define VFD_A0_PIN			1
#define VFD_WR_PORT			VFD_CTL_PORT
#define VFD_WR_PIN			0
#define VFD_BUSY_PORT		VFD_CTL_PORT
#define VFD_BUSY_PIN		3

#define VFD_CTL_LUM_100     0x01
#define VFD_CTL_LUM_075     0x02
#define VFD_CTL_LUM_050     0x03
#define VFD_CTL_LUM_025     0x04

#define VFD_CTL_BKSP        0x08
#define VFD_CTL_HTAB        0x09
#define VFD_CTL_LF          0x0A
#define VFD_CTL_CLS         0x0C
#define VFD_CTL_CR          0x0D
#define VFD_CTL_CUR_ON      0x13
#define VFD_CTL_CUR_OFF     0x14
#define VFD_CTL_CUR_FLASH   0x15
#define VFD_CTL_CUR_ULINE   0x16
#define VFD_CTL_CUR_INV     0x18

enum {
    kVFDLuminance1 = VFD_CTL_LUM_025,
    kVFDLuminance2 = VFD_CTL_LUM_050,
    kVFDLuminance3 = VFD_CTL_LUM_075,
    kVFDLuminance4 = VFD_CTL_LUM_100
};
typedef uint8_t LuminanceLevel;

void vfd_init(void);
void vfd_set_luminance(LuminanceLevel l);
void vfd_cls(void);
void vfd_cr(void);
void vfd_putc(char c);
void vfd_puts(const char *s);
