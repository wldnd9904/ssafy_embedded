from gpiozero import LED, Button, AngularServo
from time import sleep
from signal import pause
red = LED(27)
green = LED(14)
btn1 = Button(15)
btn2 = Button(18)
servo = AngularServo(17, min_angle=0, max_angle=90)
servo.angle = 0

def up():
    green.on()
    servo.angle = 90
    sleep(0.5)
    green.off()

def down():
    red.on()
    servo.angle = 0
    sleep(0.5)
    red.off()


btn1.when_pressed = up
btn2.when_pressed = down

pause()
