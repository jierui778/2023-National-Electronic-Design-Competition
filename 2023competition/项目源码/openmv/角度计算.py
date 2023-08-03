import sensor, image, time,math,pyb
import json

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_whitebal(False) # must be turned off for color tracking
clock = time.clock()


TRACK_THRESHOLD=(0, 32, -93, 109, -28, 127)

while(True):
    clock.tick()
    img = sensor.snapshot()
    ## 寻找最大色块
    blobs = img.find_blobs([TRACK_THRESHOLD],area_threshold=200,pixel_threshold=200)#捕捉色块
    s,x1,y1,w1,h1=0,0,0,0,0
    for i in blobs:#此方法为在嵌有字典的列表中索引值，i为每一个字典
        if i[2]*i[3] > s: #用类似冒泡排序一样找出色块最大面积
            s = i[2]*i[3]
    time.sleep_ms(100)
    img.draw_rectangle((i[0],i[1],i[2],i[3]),color=(255,0,0))#根据所得blobs的左上角顶点和长宽画出大的矩形
    theta=math.atan2((i.corners()[1][1]-i.corners()[0][1]),(i.corners()[1][0]-i.corners()[0][0]))# 计算倾斜角度
    theta=math.degrees(-theta)   # 将弧度值换算为角度值
    sx=i.corners()[0][0]
    sy=i.corners()[0][1] #给出最左边的点的坐标（x,y）
    print(theta,sx,sy)   #s给出角度,起始点的坐标

