#!/usr/bin/python
# -*- coding:utf-8 -*-

import sys
import os

picdir = "oled/OLED_Module_Code/RaspberryPi/python/pic"
libdir = "oled/OLED_Module_Code/RaspberryPi/python/lib"

if os.path.exists(libdir):
    sys.path.append(libdir)

from bmp280 import BMP280
from smbus import SMBus
from time import sleep
import logging    
import time
import traceback
from waveshare_OLED import OLED_0in96
from PIL import Image,ImageDraw,ImageFont
import subprocess
logging.basicConfig(level=logging.DEBUG)

try:
    bus = SMBus(1)
    bmp280 = BMP280(i2c_dev=bus)

    disp = OLED_0in96.OLED_0in96()
    logging.info("\r 0.96inch OLED ")
    # Initialize library.
    disp.Init()
    # Clear display.
    logging.info("clear display")
    disp.clear()
    font1=ImageFont.truetype(os.path.join(picdir,'Font.ttc'),16)
    while True:
        image1 = Image.new('1', (disp.width, disp.height), "WHITE")
        draw=ImageDraw.Draw(image1)
        temp=bmp280.get_temperature()
        date=subprocess.run("date +'%P %I:%M:%S'",shell=True,capture_output=True).stdout.decode()
        a=date[:1] 
        date=date[2:]
        date=str(chr(ord(a)-32))+"M"+date
        draw.line( [(0,0), (127,0)] )
        draw.line( [(0,0), (0,63)] )
        draw.line( [(0,63), (127,63)] )
        draw.line( [(127,0), (127,63)] )
        draw.text((20,0),date,font=font1,fill=0)
        draw.text((30,20),"현재 온도",font=font1,fill=0)
        draw.text((35,40),format(temp,".2f")+chr(int("0x00B0",16))+"C",font=font1,fill=0)
        disp.ShowImage(disp.getbuffer(image1))
        sleep(1)
        
    disp.clear()
    
except IOError as e:
    logging.info(e)
    
except KeyboardInterrupt:    
    logging.info("ctrl + c:")
    disp.module_exit()
    exit()

