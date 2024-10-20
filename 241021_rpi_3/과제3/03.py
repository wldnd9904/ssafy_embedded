from gpiozero import LED
from time import sleep

a = LED(5)
b = LED(6)
c = LED(13)
d = LED(19)
e = LED(26)
f = LED(16)
g = LED(20)
dp = LED(21)

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

number = input("숫자를 입력하세요: ")

for digit in number:
    num = int(digit)
    for pin in range(7):
        if numbers[num][pin] == 1:
            pins[pin].on()
        else:
            pins[pin].off()
    sleep(0.4)
    for pin in range(7):
        pins[pin].off()
    sleep(0.1)
