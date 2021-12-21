# Augmentation data script by Khue MH
# Copyright @ KMH
# For more information please contact khuehm@outlook.com
#This code used for rotating images
import numpy as np
import os

from numpy import expand_dims
from keras.preprocessing.image import load_img
from keras.preprocessing.image import img_to_array
from keras.preprocessing.image import ImageDataGenerator
from keras.preprocessing.image import save_img
from matplotlib import pyplot as plt

output_dir = "C:/Users/PC/Desktop/FINAL_DATASET"
input_dir = "E:/Chuyen_nganh/HK2_nam4/DoAnTotNghiep/Dataset_ver2/sau_hai_cham"

myImageGen = ImageDataGenerator(rotation_range=45)


def load_images_from_folder(folder):
    images = []
    for filename in os.listdir(folder):
        img = load_img(os.path.join(folder, filename))
        img = img_to_array(img)
        data = expand_dims(img, 0)
        gen = myImageGen.flow(data, batch_size=1)

        [_imgName, _imgType] = os.path.splitext(filename)
        
        for i in range(2):
        	myBatch = gen.next()
        	image = myBatch[0].astype('uint8')
        	print(os.path.join(output_dir, _imgName + str(i) + _imgType))  		
        	save_img(os.path.join(output_dir, _imgName + str(i) + _imgType), image)

load_images_from_folder(input_dir)

