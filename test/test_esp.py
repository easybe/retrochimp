#!/usr/bin/env python
import sys
import logging

import serial


logger = logging.getLogger(__name__)

form_data = b'{"first":"Ezra","last":"Buehler","email":"a@b.ch"}'


def main(argv):
    if len(argv) == 0:
        logger.error("No serial port provided")
        return 1

    with serial.Serial(argv[0], 9600, timeout=1) as port:
        port.write(form_data)

    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
