from gpiozero import LED
from time import sleep

led = LED(14)

while True:
    for i in range(100, 1, -5):
        led.on()
        sleep(i/100)
        led.off()
        sleep(i/100)
