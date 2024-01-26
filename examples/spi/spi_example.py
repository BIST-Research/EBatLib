#
# Author: Ben Westcott
# Date created: 1/26/24
#

from spidev import SpiDev
import sys

CHUNK_LENGTH = 64

# rpi 4 header pinout: 
# https://www.raspberrypi.com/documentation/computers/raspberry-pi.html
# Itsy Bitsy M4 pin --> rpi pin
# "SCK"             --> 23 (GPIO 11)
# "MI"              --> 21 (GPIO 9)
# "MO"              --> 19 (GPIO 10)
# D3                --> 24 (GPIO 8)
# "G"               --> 9, 25 or any GND pin

if __name__ == '__main__':

    byte_to_send = int(sys.argv[1])

    spi = SpiDev()
    spi.open(0, 0)
    spi.max_speed_hz = 12000000

    # shift out zeros from initialization
    spi.readbytes(2)

    msg = [byte_to_send for n in range(0, CHUNK_LENGTH)]
    ans = spi.xfer(msg)

    print(ans)

    spi.close()