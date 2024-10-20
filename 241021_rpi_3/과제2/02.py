from gpiozero import Button, LED
from signal import pause 

btn = Button(14)
laser = LED(15)

state = False

def laser_toggle():
    global state
    if state:
        print('off')
        laser.off()
        state = False
    else:
        print('on')
        laser.on()
        state= True

btn.when_pressed = laser_toggle

pause()
