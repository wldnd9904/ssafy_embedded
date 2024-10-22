from gpiozero import LED, Button, PWMLED
from time import sleep
from signal import pause

a = LED(5)
b = LED(6)
c = LED(13)
d = LED(19)
e = LED(26)
f = LED(16)
g = LED(20)
dp = LED(21)

motor = PWMLED(27)
led = LED(14)
btn1 = Button(15)
btn2 = Button(18)
btn3 = Button(17)

pins = [a,b,c,d,e,f,g,dp]
numbers = [
     [1, 1, 1, 1, 1, 1, 0],
     [0, 1, 1, 0, 0, 0, 0],
     [1, 1, 0, 1, 1, 0, 1],
     [1, 1, 1, 1, 0, 0, 1],
     [0, 1, 1, 0, 0, 1, 1],
     [1, 0, 1, 1, 0, 1, 1],
     [1, 0, 1, 1, 1, 1, 1],
     [1, 1, 1, 0, 0, 0, 0],
     [1, 1, 1, 1, 1, 1, 1],
     [1, 1, 1, 1, 0, 1, 1],
     [0, 0, 0, 0, 0, 0, 0],
     ]

power = 1
isOn = False


def print_num(num):
    for pin in range(7):
        if numbers[num][pin] == 1:
            pins[pin].on()
        else:
            pins[pin].off()
    

def incrementPower():
    global isOn
    global power
    if not isOn:
        return
    if power<3:
        power += 1
        motor.value = power*0.33
        print_num(power)


def decrementPower():
    global isOn
    global power
    if not isOn:
        return
    if power>1:
        power -= 1
        motor.value = power*0.33
        print_num(power)


def toggle():
    global power
    global isOn
    isOn = not isOn
    if isOn:
        led.on()
        print_num(power)
        motor.value = power*0.33
    else:
        led.off()
        print_num(10)
        motor.value = 0


btn1.when_pressed = incrementPower
btn2.when_pressed = decrementPower
btn3.when_pressed = toggle

pause()
