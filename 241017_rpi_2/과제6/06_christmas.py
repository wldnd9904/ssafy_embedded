from gpiozero import LED, Button
from time import sleep
from signal import pause

led = [LED(14),LED(15)]
button = Button(23)

mode = 0

def toggle_mode():
    global mode
    mode = 1 - mode


button.when_pressed = toggle_mode

while True:
    if mode == 1:
        led[0].on()
        led[1].off()
        sleep(0.5)
        led[0].off()
        led[1].on()
        sleep(0.5)
    else:
        led[0].on()
        led[1].on()
        sleep(0.5)
        led[0].off()
        led[1].off()
        sleep(0.5)


