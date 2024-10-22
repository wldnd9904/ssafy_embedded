from gpiozero import PWMLED
from time import sleep

led = PWMLED(14)

while True:
    i = input()
    if i == '1' and led.value < 1:
        led.value += 0.1
    elif i == '2' and led.value > 0:
        led.value -= 0.1
