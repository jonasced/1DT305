
from _pybytes import Pybytes
from _pybytes_config import PybytesConfig
import keys

conf = PybytesConfig().read_config()
pybytes = Pybytes(conf)

"""
print("Previous config:")
print(conf)

#pybytes.read_config([filename='/flash/pybytes_config.json', reconnect=False])

## Update wifi in pybytes config
ssid = keys.nakula_wifi_ssid
password = keys.nakula_wifi_password

pybytes.update_config('wifi', {'ssid': ssid, 'password': password}, permanent=True, reconnect=True, silent=False)

## Change autostart settings
#pybytes.update_config('pybytes_autostart', False, permanent=True, reconnect=False, silent=False)

## Change config file, but Syntax error in JSON!?
#Pybytes.read_config(file="config_camham.json", reconnect=False)
"""

print("Updated config:")
print(conf)

## To start pybytes manually
pybytes.start()
