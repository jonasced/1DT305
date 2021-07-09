
from _pybytes import Pybytes
from _pybytes_config import PybytesConfig
conf = PybytesConfig().read_config()
#pybytes = Pybytes(conf)

print(conf)

#Pybytes.print_config()

#pybytes.read_config([filename='/flash/pybytes_config.json', reconnect=False])


pybytes.update_config('wifi', {'ssid': 'Dazzle wifazzle_5G', 'password': 'somany_memes666'}, permanent=False, reconnect=False, silent=False)

#pybytes.update_config('pybytes_autostart', False, permanent=True, reconnect=False, silent=False)
## Syntax error in JSON!
#Pybytes.read_config(file="config_camham.json", reconnect=False)

#Pybytes.print_config()

#Pybytes.start()
