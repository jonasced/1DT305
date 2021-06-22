import pycom # "pycom" will be an error in your
# IDE because it's not on your computer, but on
# the device
import time

print("I'm updated!")

pycom.heartbeat(False)

i = 0

while i<3: #Forever loop
    pycom.rgbled(0xFF0000)  # Red
    time.sleep(1) #sleep for 1 second

    pycom.rgbled(0xFF3300)  # Orange
    time.sleep_ms(1000) #sleep for 1000 ms

    pycom.rgbled(0x00FF00)  # Green
    time.sleep(1)

    pycom.rgbled(0x9D02B7)  # Green
    time.sleep(1)
    i += 1

    print("Done")

pycom.heartbeat(True)
