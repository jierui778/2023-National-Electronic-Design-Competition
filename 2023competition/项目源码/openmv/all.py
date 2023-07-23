## 两个模型，分别是label和label1，分别对应拿在手上的数字识别和地面上的数字匹配
# Edge Impulse - OpenMV Image Classification Example
 
import sensor, image, time, os, tf,math
from pyb import UART
import ustruct

sensor.reset()                         # Reset and initialize the sensor.
sensor.set_pixformat(sensor.GRAYSCALE)    # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QVGA)      # Set frame size to QVGA (320x240)
sensor.set_windowing((320, 240))       # Set 240x240 window.
sensor.skip_frames(time=2000)          # Let the camera adjust.

## 手动添加
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)                # 关闭白平衡
sensor.skip_frames(30)                         # 跳过前30帧使相机图像稳定下来



threshold_index = 0                            # 0 for red, 1 for green, 2 for blue    定义了红色的区域
 
# Color Tracking Thresholds (L Min, L Max, A Min, A Max, B Min, B Max)
# The below thresholds track in general red/green/blue things. You may wish to tune them...，阈值需要自己调试
thresholds = [(70, 4, 18, 127, -125, 127),     # generic_red_thresholds
              (30, 100, -64, -8, -32, 32),     # generic_green_thresholds
              (0, 30, 0, 64, -128, 0)]         # generic_blue_thresholds



 
uart = UART(3, 115200)                                            # 与单片机的通信
uart.init(115200, bits=8, parity=None, stop=1)                    # 串口设置
list1=[0,0]


                
endline_type=0
net = "trained.tflite"                                            #获取文件
labels = [line.rstrip('\n') for line in open("labels.txt")]       #获取标签
net1 = "trained1.tflite" 
labels1 = [line.rstrip('\n') for line in open("labels1.txt")]

direct=0                   # 初始无方向，1为左，2为右
crosstime=0
start=0                    # 开始标志位，32发送，mv接收
stop =0                    # 终止标志位
clock = time.clock()
aa=[0,0,0,0,0,0]
num=10
roi=(0,0,0,0)
flag=10                    #4识别数字 5巡线     6匹配数字  1继续寻找 0找到数字
send_stop=0                #发送的停止位
sent_direct=0              #发送方向位，0直行 1左拐 2右拐
sent_angle=0


ROIS = [                   # 感兴趣区域，
        (0, 200, 320, 80, 0.7),
        (0, 120, 200, 80, 0.3),
        (0, 40, 320, 80, 0.1)
       ]
#roi代表三个取样区域，（x,y,w,h,weight）,代表左上顶点（x,y）宽高分别为w和h的矩形，
#weight为当前矩形的权值。注意本例程采用的QQVGA图像大小为160x120，roi即把图像横分成三个矩形。
#三个矩形的阈值要根据实际情况进行调整，离机器人视野最近的矩形权值要最大，


weight_sum = 0             # 后面巡线需要使用的，权值和初始化
for r in ROIS:
    weight_sum += r[4]     # #计算权值和。遍历上面的三个矩形，r[4]即每个矩形的权值。



# 串口输出函数
def sending_data(cx,cy,cw):
    global uart
    data = ustruct.pack("<bbhhhb",
                   0xFF,                      #帧头1
                   0xFE,                      #帧头2
                   int(cx), # up sample by 4   #数据1
                   int(cy), # up sample by 4    #数据2
                   int(cw), # up sample by 4    #数据1
                   0xFE)
    uart.write(data);   #必须要传入一个字节数组

#判断是否到达终点函数函数
def find_endline(img):    
	endbox_num = 0
	for r in img.find_rects(threshold = 10000):
		endbox_size = r.magnitude()
		endbox_w = r.w()
		endbox_h = r.h()
		k=1

		# 筛选黑色矩形大小,这个范围不是很懂，难道不应该是当大于某一个范围才算嘛？
		if (endbox_size<24000*k*k and endbox_h<25*k and endbox_w<25*k) :
			endbox_num = endbox_num + 1
	# 判断是否是终点线
	endline_type = 0
        
	if (endbox_num>2 and endbox_num<6):
		endline_type = 1 # 检测到第一条终点线
	elif(endbox_num >=6 ):
		endline_type = 2 # 检测到两条终点线
	else:
		endline_type = 0 # 未检测到终点线
    return endline_type


while(True):
    clock.tick()


    ###################先检测数字，等待开始标志位#####################同时向32发送停止信号###############
    while(start==0 and stop==0):#######################2初始复位识别数字
        img = sensor.snapshot().lens_corr(1.8)     #畸变矫正

        # 人手拿的数字识别，匹配标签和数字，画出四边形
        if 1:
    # default settings just do one detection... change them to search the image...
            for obj in tf.classify(net1, img, min_scale=1.0, scale_mul=0.8, x_overlap=0.5, y_overlap=0.5):
                img.draw_rectangle(obj.rect())                         
        # This combines the labels and confidence values into a list of tuples
                predictions_list = list(zip(labels1, obj.output()))
 
                for i in range(len(predictions_list)):               # 判断每一个数字对应的可能性，当大于可能性0.95则确定为该数字
                    if  predictions_list[i][1]>0.95:
                        num=i+1
                        flag=1


            ##########放入物品则开始，这里需要接受32的信号####
        #开始的时候不需要把停止标志位清除，因为mv只需要进行一次，返程由32独立控制
        if ():

            start=1
        
        #串口输出
        FH = bytearray([0xFF,0xFE,send_stop,sent_direct,sent_angle,0xFE])
        uart.write(FH)
        print(send_stop,sent_direct,sent_angle)

    while(start==1&stop==0):
    ########检测到一定数量的黑块则立即终止##########待补充
        if ():
            stop=1 
        




        # 循线
        if(flag==1):
            sensor.set_pixformat(sensor.RGB565)
            img = sensor.snapshot().lens_corr(1.8)
            found=0

            ## 颜色跟踪例程，捕获红色的色块，色块的范围要大于200
            for blob in img.find_blobs([thresholds[threshold_index]], pixels_threshold=200, area_threshold=200, merge=True):
            # These values depend on the blob not being circular - otherwise they will be shaky.
                if blob.elongation() > 0.5:
                    img.draw_edges(blob.min_corners(), color=(255,0,0))
                    img.draw_line(blob.major_axis_line(), color=(0,255,0))
                    img.draw_line(blob.minor_axis_line(), color=(0,0,255))
            # These values are stable all the time.
                img.draw_rectangle(blob.rect())
                img.draw_cross(blob.cx(), blob.cy())
            # Note - the blob rotation is unique to 0-180 only.
                img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
            #print(blob.corners())
                found=1                                                   #找到红线    

                if blob.w()<250:                                          # 色块宽度比较小，则此时是线                 
                ###########################循线代码###########################
                    img.draw_rectangle(blob.rect())
                    img.draw_rectangle((0,0,30,30))
                    #img.draw_rectangle((0,0,30, 30))
                    #将此区域的像素数最大的颜色块画矩形和十字形标记出来
                    img.draw_cross(blob.cx(),blob.cy())
                    centroid_sum += blob.cx() * r[4]
                    #计算centroid_sum，centroid_sum等于每个区域的最大颜色块的中心点的x坐标值乘本区域的权值
                    center_pos = (centroid_sum / weight_sum)
                    #中间公式

                    deflection_angle = 0
                    deflection_angle = -math.atan((center_pos-160)/120)
                    #角度计算.80 60 分别为图像宽和高的一半，图像大小为QQVGA 160x120.
                    #注意计算得到的是弧度值

                    deflection_angle = math.degrees(deflection_angle)
                    #将计算结果的弧度值转化为角度值

                    sent_angle=deflection_angle+66                  ## 为什么要+66不是很理解？


                else:                                               #色块宽度足够大，此时是十字/T字      切换至数字寻找数字
                    sent_stop=1                                     #此时小车停止，等待识别     
                    sent_angle=0     
                    flag=2
            #print(blob.cx(),blob.w(),blob.rotation_deg())


            if found==0:
                sent_stop=1                                          #对应上面颜色追踪得到的置1，没识别到红线则停车 保持巡线模式
                sent_angle=0
    

            ########################数字识别#################
        if(flag==2):
            sensor.set_pixformat(sensor.GRAYSCALE)
            img = sensor.snapshot().lens_corr(1.8)     # 畸变矫正
            img1=img
            found=0
            # 下面的`threshold`应设置为足够高的值，以滤除在图像中检测到的具有
            # 低边缘幅度的噪声矩形。最适用与背景形成鲜明对比的矩形。
            #寻找第一个数字
            for r in img.find_rects(threshold = 10000):
                img.draw_rectangle(r.rect(), color = (255, 0, 0))        # 在对应的数字画出一个矩形再进行数字识别，简化
                for p in r.corners(): img.draw_circle(p[0], p[1], 5, color = (0, 255, 0))
                #print(r1.x(),r1.y(),r1.w(),r1.h())
                roi=[r.x(),r.y(),r.w(),r.h()]
                img1=img.copy(1,1,roi,True)
    
                #print(roi1)
    
                # 对地面的数字进行匹配，输出为标签
                for obj1 in tf.classify(net, img1, min_scale=1.0, scale_mul=0.8, x_overlap=0.5, y_overlap=0.5):
                    img1.draw_rectangle(obj1.rect())
                    # This com  bines the  labels and confidence values into a list of tuples
                    predictions_list = list(zip(labels, obj1.output()))

                    # 前面得到的num是读出来的，当相同的位置（也就是与该数字的）可能性大于0.6我们认为是该数字，此时我们是通过一开始读取的
                    # 值得到对应的位置，因为从0开始，所以比如说5对应的数组位置是4，此时我们只需要判断这个框内的数字是对应第4数组（也就是数字5）
                    # 的可能性，就可以判断此时这个框内是不是一开始读取的数字
                    if  predictions_list[num-1][1]>0.6:
                        found=1
                        ## 此时这个数字所在的矩形的宽度和起始点的位置来判断这个矩形在左边/右边
                        if  r.x()+r.w()/2<140:  #####左拐
                            sent_direct=1
                            sent_stop=0
                        else: 
                            sent_direct=2       #####右拐
                            sent_stop=0
                            
        FH = bytearray([0xFF,0xFE,send_stop,sent_direct,sent_angle,0xFE])
        uart.write(FH)
        print(send_stop,sent_direct,sent_angle) 

