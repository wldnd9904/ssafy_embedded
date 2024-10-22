from gpiozero import RotaryEncoder, Button, PWMLED
from signal import pause

rotor = RotaryEncoder(20,21, wrap=True, max_steps=180)
rotor.steps = -180
rot_btn = Button(16)

led1 = PWMLED(14)
led2 = PWMLED(15)
led3 = PWMLED(18)

isOn = True

def change_rot():
    global isOn
    angle = rotor.steps
    print(angle)
    led1.value = 0
    led2.value = 0
    led3.value = 0
    if not isOn:
        return 
    if angle in range(-180, -60):
        led1.value = (angle+180)/120
    elif angle in range(-60, 60):
        led2.value = (angle+60)/120
    elif angle in range(60, 180):
        led3.value = (angle-60)/120

def click_btn():
    global isOn
    print("GD")
    isOn = not isOn
    print(isOn)
    change_rot()

rotor.when_rotated = change_rot
rot_btn.when_pressed = click_btn
pause()
