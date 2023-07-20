#import sensor, image, time,math,pyb
#from pyb import UART,LED
#import json
#import ustruct

#sensor.reset()
#sensor.set_pixformat(sensor.RGB565)
#sensor.set_framesize(sensor.QVGA)
#sensor.skip_frames(time = 2000)
#sensor.set_auto_gain(False) # must be turned off for color tracking
#sensor.set_auto_whitebal(False) # must be turned off for color tracking
#clock = time.clock()

#uart = UART(3,115200)   #定义串口3变量
#uart.init(115200, bits=8, parity=None, stop=1) # init with given parameters

#list1=[0,0]
#def sending_data(cx,cy,cw,ch):
    #global uart;
    #data = ustruct.pack("<bbhhhhhhb",
                   #0xFF,                      #帧头1
                   #0xFE,                      #帧头2
                   #int(cx), # up sample by 4   #数据1
                   #int(cy), # up sample by 4    #数据2
                   #int(cw), # up sample by 4    #数据1
                   #int(ch), # up sample by 4    #数据2
                   #int(list[0]),
                   #int(list[1]),
                   #0xFE)
    #uart.write(data);   #必须要传入一个字节数组


#while(True):
    #clock.tick()
    #img = sensor.snapshot()
    #cx=1
    #cy=30
    #cw=3
    #ch=4
    #k=55
    #if(k>255):
        #list1[0]=k//256
        #list1[1]=k%256
    #else:
        #list1[0]=0
        #list1[1]=k

    #FH = bytearray([0xFF,0xFE,cx,cy,cw,ch,list1[0],list1[1],0xFE])
    #uart.write(FH)
    #print(cx,cy,cw,ch,list1[0],list1[1])




import pyb,sensor,image,time
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)

sensor.set_auto_exposure(0)         # 设置自动曝光
sensor.set_auto_gain(False) # 颜色跟踪必须关闭增益
sensor.set_auto_whitebal(False) # 颜色跟踪必须关闭白平衡

sensor.skip_frames(time = 2000)
clock = time.clock()

