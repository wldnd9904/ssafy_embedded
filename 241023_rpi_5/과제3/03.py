from gpiozero import PWMLED, Button
from signal import pause
r = PWMLED(19)
g = PWMLED(26)
b = PWMLED(13)
rbutton = Button(14)
gbutton = Button(15)
bbutton = Button(18)


def enlighten(led): 
    if led.value == 1:
        led.value = 0
    else:
        led.value += 0.1

rbutton.when_pressed = lambda: enlighten(r)
gbutton.when_pressed = lambda: enlighten(g)
bbutton.when_pressed = lambda: enlighten(b)

r.value = 1
g.value = 1
b.value = 1

pause()
