from gpiozero import LED, Button
from time import sleep
from signal import pause

led = [LED(14),LED(15),LED(18)]
button = [Button(23), Button(24)]

def blink_in_sequence():
    print("blink in sequence")
    for i in range(3):
        led[i].on()
        sleep(0.5)
        led[i].off()
        sleep(0.5)


def blink_simultaneously():
    print("blink simultaneously")
    for i in range(3):
        for j in range(3):
            led[j].on()
        sleep(0.5)
        for j in range(3):
            led[j].off()
        sleep(0.5)


button[0].when_pressed = blink_in_sequence
button[1].when_pressed = blink_simultaneously

pause()
