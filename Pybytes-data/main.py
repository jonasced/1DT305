import time
from _pybytes import Pybytes
from _pybytes_config import PybytesConfig
import keys

conf = PybytesConfig().read_config()
pybytes = Pybytes(conf)

pybytes.start()

i = 0

while i<5:
    #The value can be a sensor reading being done here
    value = 5

    #Sending to pybytes in channel 1
    pybytes.send_signal(1, value)
    print("sending: {}".format(value))

    #Send every 5 seconds
    time.sleep(5)
    i += 1
