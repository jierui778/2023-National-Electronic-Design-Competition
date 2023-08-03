# # Untitled - By: zzy - 周五 11月 25 2022

# import sensor, image, time
# from pyb import UART
# import json

# output_str_green="[0,0]"
# output_str_red="[0,0]"
# output_str_blue="[0,0]"
# output_str_brown="[0,0]"
# output_str_yellow="[0,0]"

# #green_threshold  = (   0,   80,  -70,   -10,   -0,   30)
# green_threshold  = (   3,   39,  -29,   2,   1,   25)
# red_threshold    = (   28,   40,  51,   65,   22,   50)
# orange_threshold = (   23,   39,  19,   42,   13,   31)
# blue_threshold  = (   50,   56,  -14,   1,   -31,   -13)
# brown_threshold  = (   22,   30,  1,   17,   8,   25)
# yellow_threshold  = (   53,   58,  -7,   3,   58,   63)

# sensor.reset()
# sensor.set_pixformat(sensor.RGB565)
# sensor.set_framesize(sensor.QVGA)
# sensor.set_windowing((0,20,320,200))#QVGA find Region Of Interest
# #sensor.set_windowing((5,10,160,95))#QQVGA find Region Of Interest

# sensor.skip_frames(200)
# sensor.set_auto_whitebal(False)
# sensor.set_auto_gain(False)
# clock = time.clock()

# uart = UART(3, 115200)
# def find_max(blobs):
#     max_size=0
#     for blob in blobs:
#         if blob.pixels() > max_size:
#             max_blob=blob
#             max_size = blob.pixels()
#     return max_blob

# def detect(max_blob):#输入的是寻找到色块中的最大色块
#     #print(max_blob.solidity())
#     shape=0
#     if max_blob.solidity()>0.90 or max_blob.density()>0.84:
#         img.draw_rectangle(max_blob.rect(),color=(255,255,255))
#         shape=1

#     elif max_blob.density()>0.6:
#         img.draw_circle((max_blob.cx(), max_blob.cy(),int((max_blob.w()+max_blob.h())/4)))
#         shape=2

#     elif max_blob.density()>0.4:
#         img.draw_rectangle(max_blob.rect(),color=(0,0,0))
#         shape=3

#     return shape

# while(True):
#     #clock.tick()
#     img = sensor.snapshot() # 从感光芯片获得一张图片
#     # blobs_green = img.find_blobs([green_threshold])#找到绿色色块
#     blobs_red = img.find_blobs([red_threshold])#找到红色色块
#     #blobs_orange = img.find_blobs([orange_threshold])
#     # blobs_blue = img.find_blobs([blue_threshold])
#     # blobs_brown = img.find_blobs([brown_threshold])
#     # blobs_yellow = img.find_blobs([yellow_threshold])

#     # if blobs_green:
#     #     max_blob_green=find_max(blobs_green)
#     #     shape_green=detect(max_blob_green)
#     #     #img.draw_rectangle(max_blob_green.rect(),color=(0,255,0))#画框
#     #     img.draw_cross(max_blob_green.cx(), max_blob_green.cy(),color=(0,255,0))#画十字准星
#     #     output_str_green="[%d,%d,%d]" % (max_blob_green.cx(),max_blob_green.cy(),shape_green) #方式1
#     #     print('green:',output_str_green)

#     # else:
#     #     print('not found green!')


#     if blobs_red:
#         max_blob_red=find_max(blobs_red)
#         shape_red=detect(max_blob_red)
#         img.draw_rectangle(max_blob_red.rect(),color=(255,0,0))
#         img.draw_cross(max_blob_red.cx(), max_blob_red.cy(),color=(255,0,0))
#         output_str_red="[%d,%d,%d]" % (max_blob_red.cx(),max_blob_red.cy(),shape_red) #方式1
#         print('red:',output_str_red)

#     else:
#         print('not found red !')


#     #if blobs_orange:
#         #max_blob_orange=find_max(blobs_orange)
#         #detect(max_blob_orange)
#         ##img.draw_rectangle(max_blob_orange.rect(),color=(255,128,0))
#         #img.draw_cross(max_blob_orange.cx(), max_blob_orange.cy(),color=(255,128,0))
#         #output_str_orange="[%d,%d]" % (max_blob_orange.cx(),max_blob_orange.cy()) #方式1
#         #print('orange:',output_str_orange)
#         #uart.write(output_str_orange+'\r\n')
#     #else:
#         #print('not found orange !')


#     # if blobs_blue:
#     #     max_blob_blue=find_max(blobs_blue)
#     #     shape_blue=detect(max_blob_blue)
#     #     #img.draw_rectangle(max_blob_blue.rect(),color=(0,0,255))
#     #     img.draw_cross(max_blob_blue.cx(), max_blob_blue.cy(),color=(0,0,255))
#     #     output_str_blue="[%d,%d,%d]" % (max_blob_blue.cx(),max_blob_blue.cy(),shape_blue) #方式1
#     #     print('blue:',output_str_blue)
#     # else:
#     #     print('not found blue !')


#     # if blobs_brown:
#     #     max_blob_brown=find_max(blobs_brown)
#     #     shape_brown=detect(max_blob_brown)
#     #     #img.draw_rectangle(max_blob_brown.rect(),color=(205,133,63))
#     #     img.draw_cross(max_blob_brown.cx(), max_blob_brown.cy(),color=(205,133,63))
#     #     output_str_brown="[%d,%d,%d]" % (max_blob_brown.cx(),max_blob_brown.cy(),shape_brown) #方式1
#     #     print('brown:',output_str_brown)
#     # else:
#     #     print('not found brown !')

#     # if blobs_yellow:
#     #     max_blob_yellow=find_max(blobs_yellow)
#     #     shape_yellow=detect(max_blob_yellow)
#     #     #img.draw_rectangle(max_blob_yellow.rect(),color=(255,255,0))
#     #     img.draw_cross(max_blob_yellow.cx(), max_blob_yellow.cy(),color=(255,255,0))
#     #     output_str_yellow="[%d,%d,%d]" % (max_blob_yellow.cx(),max_blob_yellow.cy(),shape_yellow) #方式1
#     #     print('yellow:',output_str_yellow)
#     # else:
#     #     print('not found yellow !')


#     uart.write(output_str_green + output_str_red + output_str_blue + output_str_brown + output_str_yellow + '\r\n')

#     #print(clock.fps())

import sensor,pyb,time,image
from pyb import UART,LED

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time=20)
sensor.set_windowing((240, 240))
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)

red_threshold=(10,100,127,32,-43,67)


clock = time.clock()

uart=UART(3,115200)
uart.init(115200,bits=8,parity=None,stop=1)

def find_max(blobs):
    max_size=0
    for blob in blobs:
        if blob.pixels()>max_size:
            max_blob=blob
            max_size=blob.pixels()
            return max_blob


while(True):
    clock.tick()
    img=sensor.snapshot()
    blobs=img.find_blobs([red_threshold])
    max_b=find_max(blobs)
    cx=0;cy=0;
    img.draw_cross(120,120,size=5,color=(255,0,0))
    if blobs:
        cx=max_b.cx()
        cy=max_b.cy()
        img.draw_rectangle(max_b[0:4],color=(255,0,0))
        img.draw_cross(max_b[5],max_b[6])
        print(cx,cy)
