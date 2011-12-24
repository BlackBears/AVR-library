/**
 *  \file       mcp23017.h
 *  \details    This is the header file for interface to the MCP23017
 *  \author     Alan K. Duncan <duncan.alan@mac.com>
 *  \version    1.0
 *  \date       2011-12-23
 *  \warning    Requires Pascal Stang's i2cmaster.h and i2cmaster.S.  The latter
 *              needs to be modified with the specifications of the target 
 *              AVR.
 *  \copyright  MIT license
 */
 
#ifndef MCP23017_H_
#define MCP23017_H_

#include "global.h"     //  should define F_CPU here
#include <inttypes.h>

/************************************************************************/
/* MCP23017 REGISTER DEFINITIONS                                        */
/************************************************************************/
#define MCP23017_IODIRA 0x00
#define MCP23017_IODIRB 0x01
#define MCP23017_IPOLA 0x02
#define MCP23017_IPOLB 0x03
#define MCP23017_GPINTENA 0x04
#define MCP23017_GPINTENB 0x05
#define MCP23017_DEFVALA 0x06
#define MCP23017_DEFVALB 0x07
#define MCP23017_INTCONA 0x08
#define MCP23017_INTCONB 0x09
#define MCP23017_IOCON 0x0A
#define MCP23017_GPPUA 0x0C
#define MCP23017_GPPUB 0x0D
#define MCP23017_INTFA 0x0E
#define MCP23017_INTFB 0x0F
#define MCP23017_INTCAPA 0x10
#define MCP23017_INTCAPB 0x11
#define MCP23017_GPIOA 0x12
#define MCP23017_GPIOB 0x13
#define MCP23017_OLATA 0x14
#define MCP23017_OLATB 0x15

/** \struct     MCP23017
 *  \brief      Used to define a MCP23017 device on the I2C bus
 *  \details    MCP23017 type is used to hold the device address and the data to *              be written to the device (or read from the device)
 */
typedef struct {
	u08 address;	//	the address of the device
	u16 data;		//	data to/from device
} MCP23017;

/** \fn         void mcp23017_init(MCP23017 *obj, u08 address)
 *  \brief      Initialize the MCP23017 device.
 *  \details    Setup the device to use on the I2C bus.
 *  \param      address The u08 address should just be the hardware address
 *              component setup at the circuit level, i.e. at A2-A0 (e.g.
 *              0b000 if all are GND.)
 */
void mcp23017_init(MCP23017 *obj, u08 address);

/** \fn         void mcp23017_write(MCP23017 *object)
 *  \brief      Writes 16 bits of data
 *  \details    Write 16 bits of data to the device with the GPIOA register
 *              representing the lower 8 bits and GPIOB the upper 8 bits.
 *  \param      object A pointer to the MCP23017 structure.  Its data
 *              member should hold the data to be written.
 */
void mcp23017_write(MCP23017 *object);

/** \fn         mcp23017_write_register( MCP23017 *obj, u08 reg, u08 data)
 *  \brief      Writes data to register
 *  \param      obj A pointer to the MCP23017 structure.
 *  \param      reg The register to be written as u08.
 *  \param      data The data to be written as u08.
 */
void mcp23017_write_register( MCP23017 *obj, u08 reg, u08 data);

/** \fn         mcp23017_read_register( MCP23017 *obj, u08 reg)
 *  \brief      Reads a register
 *  \param      obj A pointer to the MCP23017 structure.
 *  \param      reg The register to be read as u08.  
 *  \return     The method returns the contents of the specified register as u08
 */
u08 mcp23017_read_register( MCP23017 *obj, u08 reg);

/** \fn         mcp23017_write_word( MCP23017 *obj, u08 reg )
 *  \brief      Writes 16 bits of data.  Assumes sequential mode.
 *  \param      obj A pointer to the MCP23017 structure.
 *  \param      reg The register to be written as u08.
 */
void mcp23017_write_word( MCP23017 *obj, u08 reg );

#endif /* MCP23017_H_ */