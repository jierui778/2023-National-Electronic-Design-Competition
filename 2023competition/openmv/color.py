import sensor, image, time
#red_threshold_01 = (45, 100, -60, 80, 34, 91)
red_threshold_01 = (21, 29, -72, 6, -11, 17)
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(20)
sensor.set_auto_whitebal(False)
#关闭白平衡。白平衡是默认开启的，在颜色识别中，需要关闭白平衡
clock = time.clock()
img = sensor.snapshot()
blobs = img.find_blobs([red_threshold_01],
                         area_threshold=150)
last_blobs = blobs
while(True):
    clock.tick()
    img = sensor.snapshot()
    if last_blobs:
         for b in blobs:
            x1 = b[0]-7
            y1 = b[1]-7
            w1 = b[2]+12
            h1 = b[3]+12
            #print(b.cx(),b.cy())
         roi2 = (x1,y1,w1,h1)
         print(roi2)
         blobs = img.find_blobs([red_threshold_01],
                                    roi = roi2,
                                    area_threshold=1000)
         last_blobs = blobs
    else:
        blobs = img.find_blobs([red_threshold_01],
                                    area_threshold=1000)
        last_blobs = blobs
    if last_blobs:
        #如果找到了目标颜色
        #  print(blobs)
        for b in last_blobs:#迭代找到的目标颜色区域
            img.draw_rectangle(b[0:4])
            img.draw_cross(b[5], b[6])
    print("帧率 : ",clock.fps())

