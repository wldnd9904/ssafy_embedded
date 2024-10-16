from gpiozero import LED
from time import sleep

led = [0, LED(14),LED(15),LED(18)]
num = [1,2,3]

while True:
    ledno = int(input("INPUT>> "))
    if ledno not in num:
        break
    if led[ledno].is_lit:
        led[ledno].off()
    else:
        led[ledno].on()
