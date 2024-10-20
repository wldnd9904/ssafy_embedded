from gpiozero import LED, Button
from time import sleep

a = LED(5)
b = LED(6)
c = LED(13)
d = LED(19)
e = LED(26)
f = LED(16)
g = LED(20)
dp = LED(21)

led = LED(14)
button = Button(15)

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
     [1, 1, 1, 1, 0, 1, 1]
     ]

def print_num(num):
    for pin in range(7):
        if numbers[num][pin] == 1:
            pins[pin].on()
        else:
            pins[pin].off()
    
    
def check_num(num):
    if button.is_pressed:
        if num == 7:
            for _ in range(3):
                led.on()
                sleep(0.5)
                led.off()
                sleep(0.5)
        else:
            sleep(1)


while True:
    for num in range(1,10):
        print_num(num)
        check_num(num)
        sleep(0.1)
    sleep(0.4)
    for num in range(8,-1,-1):
        print_num(num)
        check_num(num)
        sleep(0.1)
    sleep(0.4)
