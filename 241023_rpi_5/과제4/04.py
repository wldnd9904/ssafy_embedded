from gpiozero import LED, Button
from time import sleep

led = LED(14)
btn1 = Button(15)
btn2 = Button(18)

duty = 1

def incrementDuty():
    global duty
    if duty < 9:
        duty += 1


def decrementDuty():
    global duty
    if duty > 1:
        duty -= 1


btn1.when_pressed = incrementDuty
btn2.when_pressed = decrementDuty

while True:
    for i in range(10):
        if i < duty:
            led.on()
        else:
            led.off()
        sleep(0.002)


