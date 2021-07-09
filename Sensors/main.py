import machine
import time

# Temperature sensor
adc = machine.ADC()
temppin = adc.channel(pin='P16')

while True:
    mv = temppin.voltage()
    print(mv, "mV")
    celsius = (mv - 500.0) / 10.0
    print("Celsius:", celsius)
    time.sleep(1)
