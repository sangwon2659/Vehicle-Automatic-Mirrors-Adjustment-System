#
#   Headpose Detection for Video
#   Written by Qhan
#   Last Update: 2019.1.9
#

import argparse
import cv2
import numpy as np
import os.path as osp

import headpose
from utils import Annotator

faceCascade = cv2.CascadeClassifier('haarcascade_profileface.xml')

def main(args):
    filename = args["input_file"]

    if filename is None:
        isVideo = False
        cap = cv2.VideoCapture(0)
        #cap2=cv2.VideoCapture(0)
        cap.set(3, args['wh'][0])
        cap.set(4, args['wh'][1])

    # Initialize head pose detection
    hpd = headpose.HeadposeDetection(args["landmark_type"], args["landmark_predictor"])

    x_list = []
    y_list = []
    z_list = []
    count = 0
    t=0
    while(t<100):
        t+=1
        # Capture frame-by-frame
        print('\rframe: %d' % count, end='')
        ret, frame = cap.read()
        frame = cv2.flip(frame, 1)
        frame, angles = hpd.process_image(frame)
        print(angles)
        if angles!=None:
            x,y,z=angles
            x_list.append(x)
            y_list.append(y)
            z_list.append(z)
            # Display the resulting frame
        cv2.imshow('frame', frame)
            
        if cv2.waitKey(1) & 0xFF == ord('q'):
            headpose.t.summary()
            break

        count += 1
    x_avg=sum(x_list)/len(x_list)
    y_avg=sum(y_list)/len(y_list)
    z_avg=sum(z_list)/len(z_list)
    print("The average direction value is x: {}, y: {} z: {}".format(x_avg, y_avg, z_avg))
    Annotator.avg()
    # When everything done, release the capture
    cap.release()
    if isVideo: out.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-i', metavar='FILE', dest='input_file', default=None, help='Input video. If not given, web camera will be used.')
    parser.add_argument('-o', metavar='FILE', dest='output_file', default=None, help='Output video.')
    parser.add_argument('-wh', metavar='N', dest='wh', default=[640, 480], nargs=2, help='Frame size.')
    parser.add_argument('-lt', metavar='N', dest='landmark_type', type=int, default=1, help='Landmark type.')
    parser.add_argument('-lp', metavar='FILE', dest='landmark_predictor', 
                        default='model/shape_predictor_68_face_landmarks.dat', help="Landmark predictor data file.")
    args = vars(parser.parse_args())
    main(args)
