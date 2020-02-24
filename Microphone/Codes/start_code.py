import os
import RPi.GPIO as GPIO
import time
import subprocess
import os

onoff=False
music_onoff=False

try:
    while True:
        if onoff==False:
#            os.system("python example.py")
            Maria=subprocess.Popen("python example.py -x", shell=True)
            Maria.wait()
            Maria.kill()
            onoff=True
            time.sleep(0.5)
        elif onoff==True:
            print("촬영 시작")
            os.system("omxplayer Start.wav")
            os.system("python Calculation.py")
            onoff=False

except KeyboardInterrupt:
    pass
