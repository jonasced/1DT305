from network import WLAN
import machine
import time

def wlan_connect_static():
    # Static IP setup, works???
    wlan = WLAN() # get current object, without changing the mode
    if machine.reset_cause() != machine.SOFT_RESET:
        wlan.init(mode=WLAN.STA)
        # configuration below MUST match your home router settings!!
        wlan.ifconfig(config=('192.168.178.107', '255.255.255.0', '192.168.1.1', '127.0.0.53')) # (ip, subnet_mask, gateway, DNS_server)

    if not wlan.isconnected():
        # change the line below to match your network ssid, security and password
        wlan.connect(ssid="Hackernet", auth=(WLAN.WPA2, "Ubiquiti1337"), timeout=5000)
        print("connecting",end='')
        while not wlan.isconnected():
            time.sleep(1)
            print(".",end='')
        print("WiFi connected succesfully")
        print(wlan.ifconfig())

wlan_connect_static()

print("New code uploaded")
