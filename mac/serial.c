#include "serial.h"

#include <stdio.h>
#include <string.h>
#include <Serial.h>
#include <Devices.h>

#define MODEM_PORT_OUT "\p.AOut"
#define MODEM_PORT_IN "\p.AIn"
#define PRINTER_PORT_OUT "\p.BOut"
#define PRINTER_PORT_IN "\p.BIn"

OSErr writeSerialPort(short refNum, const char *str)
{
    const char *nameStr = "";
    switch (refNum) {
        case aoutRefNum:
            nameStr = MODEM_PORT_OUT;
            break;
        case boutRefNum:
            nameStr = PRINTER_PORT_OUT;
            break;
        default:
            return -1;
    }
    short serialPort = 0;
    OSErr err = MacOpenDriver(nameStr, &serialPort);
    if (err < 0) {
        return err;
    }
    CntrlParam cb;
    cb.ioCRefNum = serialPort;
    cb.csCode = 8;
    cb.csParam[0] = stop10 | noParity | data8 | baud9600;
    err = PBControl((ParmBlkPtr)&cb, 0);
    if (err < 0) {
        return err;
    }
    IOParam pb;
    pb.ioRefNum = serialPort;
    pb.ioBuffer = (Ptr)str;
    pb.ioReqCount = strlen(str);
    err = PBWrite((ParmBlkPtr)&pb, 0);
    if (err < 0) {
        return err;
    }
    err = MacCloseDriver(serialPort);
    return err;
}

void println(const char *str, ...)
{
    char buf[1024];
    va_list args;
    va_start(args, str);
    vsprintf(buf, str, args);
    strcat(buf, "\r\n");
    writeSerialPort(boutRefNum, buf);
    va_end(args);
}
