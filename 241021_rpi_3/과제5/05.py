from gpiozero import LED, DistanceSensor
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

num = 0

sensor = DistanceSensor(echo=15, trigger=14)

prev_distance = 1

while True:
    cur_distance = sensor.distance
    if prev_distance == 1 and cur_distance != 1:
        num = (num+1)%10
    prev_distance = cur_distance

    for pin in range(7):
        if numbers[num][pin] == 1:
            pins[pin].on()
        else:
            pins[pin].off()

    sleep(0.1)
