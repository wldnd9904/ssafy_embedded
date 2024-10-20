from gpiozero import TonalBuzzer
from gpiozero.tones import Tone
from time import sleep

lst = [415.30, 329.63, 369.99, 329.63, 493.88, 415.30, 554.37, 493.88, 329.63]
length = [4, 2, 2, 2, 4, 2, 2, 2, 2]
pause = [0, 0, 4, 4, 0, 0, 4, 4, 10]

b = TonalBuzzer(14)

while True:
    for i in range(9):
        b.play(lst[i])
        sleep(length[i]/16)
        b.stop()
        sleep(pause[i]/16)
    break
