# -*- coding: utf-8 -*-
"""
Created on Wed Apr 24 15:35:30 2019

@author: sangwon
"""

# -*- coding: utf-8 -*-
"""
Created on Mon Apr 22 15:22:10 2019

@author: sangwon
"""

import numpy as np
import cv2

# multiple cascades: https://github.com/Itseez/opencv/tree/master/data/haarcascades
faceCascade = cv2.CascadeClassifier('haarcascade_profileface.xml')
 
cap = cv2.VideoCapture(0)
cap.set(3,640) # set Width
cap.set(4,480) # set Height
z=[]
for x in range(100):
    ret, img = cap.read()
    #img = cv2.flip(img, -1)
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = faceCascade.detectMultiScale(
        gray,
        scaleFactor=1.3,
        minNeighbors=5,      
        minSize=(30, 30)
    )
    for (x,y,w,h) in faces:
        cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
        roi_gray = gray[y:y+h, x:x+w]
        roi_color = img[y:y+h, x:x+w]
        z.append(x+w)
    cv2.imshow('video', img)
        
    k = cv2.waitKey(30) & 0xff
    if k == 27: # press 'ESC' to quit
        break
z_avg=sum(z)/len(z)
print(z)

cap.release()
cv2.destroyAllWindows()