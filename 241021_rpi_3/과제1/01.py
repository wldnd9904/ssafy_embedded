from gpiozero import Button, LED
from signal import pause 

btn = Button(14)
laser = LED(15)

def laser_on():
    print('on')
    laser.on()


def laser_off():
    print('off')
    laser.off()


btn.when_pressed = laser_on
btn.when_released = laser_off

pause()
