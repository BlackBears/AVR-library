2011-12-24

To use this in an AVR application, you will need files from avrlib

global.h
i2cmaster.h
i2cmaster.S

You will need to modify i2cmaster.S with the proper pins to use, or for ATtiny 4313, just use the one that 
is in *this* folder.