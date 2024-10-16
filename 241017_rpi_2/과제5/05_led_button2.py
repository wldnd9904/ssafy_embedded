from gpiozero import LED, Button
from time import sleep
from signal import pause

led = [LED(14),LED(15),LED(18)]
button = [Button(23), Button(24)]

cur = 0

def next():
    global cur
    print("next")
    led[cur].off()
    cur = (cur+1)%3
    led[cur].on()

def reset():
    global cur
    print("reset")
    cur = 0
    led[0].on()
    led[1].off()
    led[2].off()

reset()

button[0].when_pressed = next
button[1].when_pressed = reset

pause()
