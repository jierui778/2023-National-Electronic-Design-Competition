import sensor, image, time,math,pyb
from pyb import UART,LED
import json
import ustruct

'''sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_whitebal(False) # must be turned off for color tracking
clock = time.clock()'''
uart = UART(3,115200)   #定义串口3变量
uart.init(115200, bits=8, parity=None, stop=1) # init with given parameters


def sending_data(a,b,c,d,e,f):
    global uart;
    data = ustruct.pack("<bbhhhhhhb",
                   0xFF,                      #帧头1
                   0xFE,                      #帧头2
                   int(a), # up sample by 4   #数据1
                   int(b), # up sample by 4    #数据2
                   int(c), # up sample by 4    #数据1
                   int(d), # up sample by 4    #数据2
                   int(e),
                   int(f),
                   0xFE)
    uart.write(data);   #必须要传入一个字节数组

def find_blob_center(threshold):
    blobs = img.find_blobs([threshold])
    if blobs:
        b = blobs[0]
        cx = b.cx()
        cy = b.cy()
        return cx, cy
    return 0, 0


red_threshold = (75, 100, -39, 67, -25, 23) # 红色激光笔的颜色阈值
green_threshold = (75, 100, -39, 67, -25, 23)  # 绿色十字的颜色阈值
(95, 100, -6, 55, -72, 110)



TRACK_THRESHOLD=(0, 0, -33, 127, -14, 127)
sx=0
sy=0
laser_x=0
laser_y=0
list1=[0,0]
flag=1;
while(True):

    if (flag==1):
        sensor.set_pixformat(sensor.GRAYSCALE)
        sensor.set_framesize(sensor.QQVGA)
        sensor.skip_frames(time = 2000)
        sensor.set_auto_gain(False)
        sensor.set_auto_exposure(False,1000)
        sensor.set_auto_whitebal(False)
        clock = time.clock()
        clock.tick()
        img = sensor.snapshot().lens_corr(strength=1.6, zoom=1.0)

        # 检测红色激光笔的位置
        laser_x, laser_y = find_blob_center(red_threshold)
        if laser_x is not None and laser_y is not None:
            # 绘制绿色十字来表示激光笔的位置
            img.draw_cross(laser_x, laser_y, color=(0, 255, 128))
            #img.draw_circle(80, 60, color=(0, 255, 128))
        print(laser_x,laser_y)
        # 显示图像
        img.draw_cross(80, 60, color=(255, 0, 0))  # 中心位置绘制红色十字
        flag=1

    if (flag ==0):
        sensor.reset()
        sensor.set_pixformat(sensor.RGB565)
        sensor.set_auto_exposure(False)
        sensor.set_framesize(sensor.QVGA)
        sensor.skip_frames(time = 2000)
        sensor.set_auto_gain(False) # must be turned off for color tracking
        sensor.set_auto_whitebal(False) # must be turned off for color tracking
        clock = time.clock()
        clock.tick()
        img = sensor.snapshot()
        ## 寻找最大色块
        blobs = img.find_blobs([TRACK_THRESHOLD],area_threshold=2000,pixel_threshold=200)#捕捉色块
        s=0
        if (blobs):
            for i in blobs:#此方法为在嵌有字典的列表中索引值，i为每一个字典
                if i[2]*i[3] > s: #用类似冒泡排序一样找出色块最大面积
                    s = i[2]*i[3]
            #time.sleep_ms(100)
            img.draw_rectangle((i[0],i[1],i[2],i[3]),color=(255,0,0))#根据所得blobs的左上角顶点和长宽画出大的矩形
            theta=math.atan2((i.corners()[1][1]-i.corners()[0][1]),(i.corners()[1][0]-i.corners()[0][0]))# 计算倾斜角度
            theta=math.degrees(-theta)   # 将弧度值换算为角度值
            sx=i.corners()[0][0]
            sy=i.corners()[0][1] #给出最左边的点的坐标（x,y）
            print(theta,sx,sy)   #s给出角度,起始点的坐标
            theta_int=int(theta*100)      #把浮点数的角度换成两个int大小
            if(theta_int>255):
                list1[0]=theta_int//256
                list1[1]=theta_int%256
            else:
                list1[0]=0
                list1[1]=theta_int
            flag=1
    FH = bytearray([0xFF,0xFE,sx,sy,list1[0],list1[1],laser_x,laser_y,0xFE])
    uart.write(FH)
    time.sleep_ms(1000)
