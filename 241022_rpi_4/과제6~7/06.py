from mfrc522 import SimpleMFRC522
from gpiozero import LED
from time import sleep
from signal import pause
import threading 

a = LED(5)
b = LED(6)
c = LED(13)
d = LED(19)
e = LED(26)
f = LED(16)
g = LED(20)
dp = LED(21)
green = LED(15)
red = LED(14)

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

def print_num(num):
    for pin in range(7):
        if numbers[num][pin] == 1:
            pins[pin].on()
        else:
            pins[pin].off()


def rfid_reader():
    global cnt
    key = 208836238120
    while True:
        id = SimpleMFRC522().read()[0]
        if id == key:
            cnt += 1
            print(f'Welcome RFID!')
            print(f'Today: {cnt}')
            print_num(cnt)
        else:
            print(f'Stranger!')
            for _ in range(5):
                red.on()
                sleep(0.2)
                red.off()
                sleep(0.2)        
        sleep(0.3)

print('Ready...')
password = '1557'
cnt = 0
thread = threading.Thread(target=rfid_reader)
thread.start()

for _ in range(3):
    green.on()
    sleep(0.5)
    green.off()
    sleep(0.5)
green.on()

print('ON')

while True:
    name = input('name: ')
    pw = input('pw: ')
    if password == pw:
        cnt += 1
        print(f'Welcome {name}!')
        print(f'Today: {cnt}')
        print_num(cnt)
    else:
        print(f'Stranger!')
        for _ in range(5):
            red.on()
            sleep(0.2)
            red.off()
            sleep(0.2)


thread.join()
