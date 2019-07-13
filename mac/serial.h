#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <MacTypes.h>

OSErr writeSerialPort(short refNum, const char *str);
void println(const char *msg, ...);

#endif
