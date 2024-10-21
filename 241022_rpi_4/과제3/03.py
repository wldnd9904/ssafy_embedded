from gpiozero import LED
from time import sleep

relay = LED(2)

while True:
    a = input('>>')
    if a=="on":
        relay.on()
    
    elif a=="off":
        relay.off()
