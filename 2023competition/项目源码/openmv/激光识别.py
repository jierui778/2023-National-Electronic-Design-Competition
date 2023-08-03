import sensor, image, time
import sensor, image, time,math,pyb
from pyb import UART,LED
import json
import ustruct



sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_exposure(False,1400)
sensor.set_auto_whitebal(False)
clock = time.clock()

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

red_threshold = (75, 100, -39, 67, -25, 23) # 红色激光笔的颜色阈值
green_threshold = (75, 100, -39, 67, -25, 23)  # 绿色十字的颜色阈值
(95, 100, -6, 55, -72, 110)

def find_blob_center(threshold):
    blobs = img.find_blobs([threshold])
    if blobs:
        b = blobs[0]
        cx = b.cx()
        cy = b.cy()
        return cx, cy
    return 0, 0

while True:
    clock.tick()
    img = sensor.snapshot().lens_corr(strength=1.6, zoom=1.0)

    # 检测红色激光笔的位置
    laser_x, laser_y = find_blob_center(red_threshold)

    if laser_x is not None and laser_y is not None:
        # 绘制绿色十字来表示激光笔的位置
        img.draw_cross(laser_x, laser_y, color=(0, 255, 128))

    # 显示图像
    img.draw_cross(80, 60, color=(255, 0, 0))  # 中心位置绘制红色十字
    time.sleep_ms(100)
    FH = bytearray([0xFF,0xFE,0,0,0,0,laser_x,laser_y,0xFE])
    if (laser_x!=0):
        print(laser_x,laser_y)
    uart.write(FH)
