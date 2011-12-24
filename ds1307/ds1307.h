/** \file       ds1307.h
 *  \details    This is the header file for interface to DS1307 RTC
 *  \author     Alan K. Duncan <duncan.alan@mac.com>
 *  \version    1.0
 *  \date       12/23/2011 8:08:20 AM
 *  \warning    Requires Pascal Stang's i2cmaster.h and i2cmaster.S.  The latter
 *              needs to be modified with the specifications of the target 
 *              AVR.
 *  \copyright  MIT license
 */

#ifndef DS1307_H_
#define DS1307_H_

#include "global.h"     //  should define F_CPU here
#include <inttypes.h>   //  if we wish to use standard integer types

/** \struct DS1307
 *  \brief  Defines data structure for date/time
 */
typedef struct {
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint8_t year;
} DS1307Date;

/** \fn         void ds1307_init()
 *  \brief      Initializes the I2C interface to the DS1307
 *  \details    Importantly, this function clears the CH bit in the seconds
 *              register (0x00) allowing the oscillator to run.
 */
void ds1307_init();

/** \fn         ds1307_read_date(DS1307Date *date)
 *  \brief      Reads date and time from the DS1307
 *  \details    Reads the data from the device and stores it in the DS1307Date
 *              structure provided.
 *  \param      date A pointer to a DS1307Date struct to be populated by the 
 *              read.
 */
void ds1307_read_date(DS1307Date *date);

/** \fn         ds1307_set_military_mode()
 *  \brief      Sets military mode (24h format)
 */
void ds1307_set_military_mode();

#endif /* DS1307_H_ */