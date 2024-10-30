from gpiozero import RotaryEncoder, Button
from signal import pause

rotor = RotaryEncoder(27,22, wrap=True, max_steps=180)
rotor.steps = -180
rot_btn = Button(17)

def change_rot():
    print(rotor.steps)

def click_btn():
    print("hi")

rotor.when_rotated = change_rot
rot_btn.when_pressed = click_btn
pause()
