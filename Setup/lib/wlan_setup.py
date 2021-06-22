from network import WLAN
import machine

# Connecting to the device
def ap_create():
    wlan = WLAN()

    wlan.init(mode=WLAN.AP, ssid='Sahadeva')
    #use the line below to apply a password
    wlan.init(ssid="Hackernet", auth=(WLAN.WPA2, "Ubiquiti1337"))
    print(wlan.ifconfig(id=1)) #id =1 signifies the AP interface

# Connecting to a router
def wlan_connect():
    wlan = WLAN(mode=WLAN.STA)

    wlan.connect(ssid="Hackernet", auth=(WLAN.WPA2, "Ubiquiti1337"))
    while not wlan.isconnected():
        machine.idle()
    print("WiFi connected succesfully")
    print(wlan.ifconfig())

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
