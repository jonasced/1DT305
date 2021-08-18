import machine
import time


# Current sensor
adc = machine.ADC()
currentpin = adc.channel(pin='P17')
VCC = 3.3
sens = 40 # 40 mV/A
QOV = VCC/2 * 1000
offset = 0
i = 0

while True:
    print("--------------", i, "--------------")

    read_value = currentpin.voltage()
    print("Read value:", read_value)

    # (5/1023.0) *  ???? why
    mv_raw = currentpin.voltage()

    print(mv_raw, "mV RAW")
    mv = mv_raw - QOV
    ampere = mv / sens
    print("Voltage:", mv, "Ampere:", ampere, " [A]")

    time.sleep(1)

    """
    # Calibration
    if i < 3:
        offset = - mv_raw + QOV
        if offset > 0.01:
            print("New offset: ", offset)
    """

    i += 1
"""
# Temperature sensor
adc = machine.ADC()
temppin = adc.channel(pin='P16')

while True:
    mv = temppin.voltage()
    print(mv, "mV")
    celsius = (mv - 500.0) / 10.0
    print("Celsius:", celsius)
    time.sleep(1)
"""
