
# boot.py
from network import LoRa
import time
import binascii
import keys

lora = LoRa(mode=LoRa.LORAWAN, region=LoRa.EU868)

app_eui = binascii.unhexlify('0000000000000000')
app_key = binascii.unhexlify(keys.app_key)

lora.join(activation=LoRa.OTAA, auth=(app_eui, app_key), timeout=0)

# wait until the module has joined the network
while not lora.has_joined():
    time.sleep(2.5)
    print('Not joined yet...')

print('Network joined!')

# main.py'

import socket
import time

# Send message
s = socket.socket(socket.AF_LORA, socket.SOCK_RAW)
s.setsockopt(socket.SOL_LORA, socket.SO_DR, 5)
s.setblocking(False)

# EXAMPLE: Create a DHT object, collect data in the loop and send it

while True:
    temperature = 23    # Mock value
    humidity = 40       # Mock value
    s.send(bytes([temperature, humidity]))
    print('sent temperature:', temperature)
    print('sent humidity:', humidity)
    time.sleep(900)     # wait 900 seconds (15 minutes) before sending again
