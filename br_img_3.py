#import cv2
#Brightness Images
import numpy as np
import os

from numpy import expand_dims
from keras.preprocessing.image import load_img
from keras.preprocessing.image import img_to_array
from keras.preprocessing.image import ImageDataGenerator
from keras.preprocessing.image import save_img
from matplotlib import pyplot as plt

output_dir = "C:/Users/PC/Desktop/FINAL_DATASET"
input_dir = "E:/Chuyen_nganh/HK2_nam4/DoAnTotNghiep/Dataset_ver2/sau_cuon_la"

def brightness_aug(folder, bri_range, img_num):
    imgGen_bri = ImageDataGenerator(brightness_range = bri_range)

    print("---------------- BRIGHTNESS ----------------\n")
    prefix = "br_"
    for filename in os.listdir(folder):
   
        [_imgName, _imgType] = os.path.splitext(filename)   

        print("[SOURCE FILE]  " + os.path.join(input_dir, filename))

        if _imgType == '.txt':
            
            for i in range(img_num):
                print(os.path.join(output_dir, prefix + _imgName + str(i) + _imgType))
                with open(os.path.join(input_dir, filename)) as f_src:
                    with open(os.path.join(output_dir, prefix + _imgName + str(i) + _imgType), "w") as f_dst:
                        for line in f_src:
                            f_dst.write(line)
                        f_dst.close()
                    f_src.close()

        else:
            img = load_img(os.path.join(folder, filename))
            img = img_to_array(img)
            data = expand_dims(img, 0)
            genBri = imgGen_bri.flow(data, batch_size=1)
            
            for i in range(img_num):
                # plt.subplot(330 + 1 + i)
                myBatch = genBri.next()
                image = myBatch[0].astype('uint8')
                print(os.path.join(output_dir, prefix + _imgName + str(i) + _imgType))  		
                save_img(os.path.join(output_dir, prefix + _imgName + str(i) + _imgType), image)
                # plt.imshow(image)

            # plt.show()

# load_images_from_folder(input_dir)
brightness_aug(input_dir, [0.05, 2], 2)


