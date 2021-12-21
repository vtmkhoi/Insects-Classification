#THIS CODE USED FOR CAPTURE IMAGE IN CERTAIN TIME AND DETECT OBJECT (WINDOW VERSION) 
#Server added
import cv2
import datetime 
import time
import json
import socket
import os 

HOST = '192.168.0.198'
PORT = 1999

#**********LOAD MODEL AND WEIGHT FROM FILE************#
confThresh = 0.4
nmsThresh  = 0.4
modelConfiguration = "E:/Chuyen_nganh/HK2_nam4/DoAnTotNghiep/yolov4-custom.cfg"
modelWeights = "E:/Chuyen_nganh/HK2_nam4/DoAnTotNghiep/yolov4-custom_last.weights"

#**********LOAD NET FROM DNN***************#
net = cv2.dnn_DetectionModel(modelConfiguration, modelWeights)
net.setInputSize(608,608)
net.setInputScale(1.0 / 255)
net.setInputSwapRB(True)

t = datetime.datetime.now() #Thoi diem thuc hien lenh.
cam = cv2.VideoCapture(0)
e = datetime.datetime.now() #thoi diem hien tai

img_counter = 0
capture_flag = 1
output_dir = "E:/Chuyen_nganh/HK2_nam4/DoAnTotNghiep/result/"

while True:
    e = datetime.datetime.now()
    if t.minute != e.minute:
    #if t.hour + 2 < e.hour:
        capture_flag = 1
    ret, frame = cam.read()
    cv2.imshow("Camera", frame)
    if not ret:
        print("failed to grab frame")
        break


    k = cv2.waitKey(1)
    if k%256 == 27:
        # ESC pressed
        print("Escape hit, closing...")
        break
    elif capture_flag==1:
        capture_flag = 0
        t = datetime.datetime.now()
        # SAVE IMAGE
        # img_name = "opencv_frame_{}.jpg".format(img_counter)
        img_name = "Ngay{0}_thang{1}_{2}gio_{3}phut.jpg".format(e.day, e.month, e.hour, e.minute)
        img = frame
        print("Capture's time:", t)
        print("current time:", e)
        c = t.hour + 3
        print("The next capture's time at:",c,"hour")
        with open('obj.names', 'rt') as f:
            start = time.time()
            names = f.read().rstrip('\n').split('\n')
            classes, confidences, boxes = net.detect(img, confThreshold=confThresh, nmsThreshold=nmsThresh)
            if(len(classes)):
                #print('class', classes)
                for classId, confidence, box in zip(classes.flatten(), confidences.flatten(), boxes):
                    accuracy = '%.2f' % confidence
                    label = '%s: %s' % (names[classId], accuracy)
                    #print("Insect's name:", names[classId], ". Accuracy:", accuracy)
                    labelSize, baseLine = cv2.getTextSize(label, cv2.FONT_HERSHEY_SIMPLEX, 0.5, 1)
                    left, top, width, height = box
                    top = max(top, labelSize[1])
                    cv2.rectangle(img, box, color=(0, 255, 255), thickness=2)
                    cv2.rectangle(img, (left, top - labelSize[1]), (left + labelSize[0], top + baseLine), (255, 255, 255), cv2.FILLED)
                    cv2.putText(img, label, (left, top), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0))
                #print number of insect detected
                print("Number of Sau_cuon_la:", len(classes[classes == 1]))
                print("Number of Sau_2_cham:", len(classes[classes == 0]))
                insects_list = {names[1]: len(classes[classes == 1]), names [0]: len(classes[classes == 0])}
                file_name = "Ngay{0}_thang{1}_{2}gio_{3}phut.txt".format(e.day, e.month, e.hour, e.minute)
                data_file = open(os.path.join(output_dir) + file_name, 'w')
                data_file.write(str(insects_list))
                data_file.close()
                data1_sending = json.dumps(insects_list)
                s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                s.connect((HOST, PORT))
                s.sendall(bytes(data1_sending, encoding = 'utf-8'))
                s.close
            else:
                print("Number of Sau_cuon_la:", len(classes))
                print("Number of Sau_2_cham:", len(classes))
                x = {names[1]: len(classes), names [0]: len(classes)}
                file_name = "Ngay{0}_thang{1}_{2}gio_{3}phut.txt".format(e.day, e.month, e.hour, e.minute)
                data_file = open(os.path.join(output_dir) + file_name, 'w')
                data_file.write(str(x))
                data_file.close()
                data_sending2 = json.dumps(x)
                s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                s.connect((HOST, PORT))
                s.sendall(bytes(data_sending2, encoding = 'utf-8'))
                s.close
            cv2.imwrite(os.path.join(output_dir, img_name), frame)
            end = time.time()
            print("Detection time: " + str(end-start))



