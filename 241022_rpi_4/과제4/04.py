#!/usr/bin/python
# -*- coding:utf-8 -*-

import sys
import os
picdir = os.path.join(os.path.dirname(os.path.dirname(os.path.realpath(__file__))), 'pic')
libdir = os.path.join(os.path.dirname(os.path.dirname(os.path.realpath(__file__))), 'lib')
if os.path.exists(libdir):
    sys.path.append(libdir)

import logging    
import time
import traceback
from waveshare_OLED import OLED_0in96
from PIL import Image,ImageDraw,ImageFont
from gpiozero import Button
from signal import pause

logging.basicConfig(level=logging.DEBUG)
btn = Button(14)
cur_img = 0
disp = OLED_0in96.OLED_0in96()


def change_img():
    global cur_img
    global disp
    cur_img = (cur_img%3)+1
    logging.info ("***draw image")
    Himage = Image.new('1', (disp.width, disp.height), 255)
    bmp = Image.open(os.path.join(picdir, f'{cur_img:02d}.bmp'))
    Himage.paste(bmp, (0,0))
    Himage=Himage.rotate(0) 	
    disp.ShowImage(disp.getbuffer(Himage))      


btn.when_pressed = change_img

try:
    logging.info("\r 0.96inch OLED ")
    # Initialize library.
    disp.Init()
    # Clear display.
    logging.info("clear display")
    disp.clear()

    # Create blank image for drawing.
    image1 = Image.new('1', (disp.width, disp.height), "WHITE")
    draw = ImageDraw.Draw(image1)
    pause()
    
    
except IOError as e:
    logging.info(e)
    
except KeyboardInterrupt:    
    logging.info("ctrl + c:")
    disp.module_exit()
    exit()
