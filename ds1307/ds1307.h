/*
 * ds1307.h
 *
 * Created: 12/23/2011 8:08:20 AM
 *  Author: Owner
 */ 


#ifndef DS1307_H_
#define DS1307_H_


#include "global.h"
#include <inttypes.h>

typedef struct {
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint8_t year;
} DS1307Date;

void ds1307_init();
void ds1307_read_date(DS1307Date *date);
void ds1307_set_military_mode();

#endif /* DS1307_H_ */