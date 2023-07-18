/*
 * @Author: Jierui 7584181012qq.com
 * @Date: 2023-07-16 15:13:16
 * @LastEditors: Jierui 7584181012qq.com
 * @LastEditTime: 2023-07-18 12:39:26
 * @FilePath: \2023电赛\competition\2023competition\项目源码\f for stm32\USER\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "stm32f10x.h"
#include "sys.h"
#include "timer.h"
#include "usart.h"
#include "encoder.h"
#include "oled.h"
#include "delay.h"
#include "usart.h"
int main(void)
{
		delay_init();
		Serial_Init();//串口和openmv传输测试
    // Encoder_Init();
    // uart_init(9600);
    // int value;
    OLED_Init();       // OLED初始化
//    OLED_ColorTurn(1); // 颜色反转
                       //    OLED_DisplayTurn(1); // 屏幕旋转
    // OLED_DisplayTurn(0);
    while (1) {

        // OLED_DrawLine(8, 1, 12, 30, 1);
        // OLED_DrawPoint(120, 6, 1);
//        OLED_DrawCircle(33, 33, 10, 1);
        // OLED_ShowChar(8, 8, 65, 16, 1);
        //        OLED_ShowString(1, 1, "charting", 16, 1);
//        OLED_ShowNum(1, 1, 6888, 4, 16, 1);
//        OLED_ShowChinese(0,0,0,64,1);//中
//		OLED_ShowChinese(0,0,1,32,1);//景
//		OLED_ShowChinese(36,0,2,16,1);//园
//		OLED_ShowChinese(54,0,3,16,1);//电
//		OLED_ShowChinese(72,0,4,16,1);//子
//		OLED_ShowChinese(90,0,5,16,1);//技
			
			
			
//			串口3调试
//			OLED_ShowNum(5,1,Serial_RxPacket[0],2,16,1);
//			OLED_ShowNum(25,1,Serial_RxPacket[1],2,16,1);
//			OLED_ShowNum(45,1,Serial_RxPacket[2],2,16,1);
//			OLED_ShowNum(65,1,Serial_RxPacket[3],2,16,1);
	
			
        OLED_Refresh();

        // value = (short)Read_Encoder(4);
        // printf("%d\n",value);
        // printf()
        //        OLED_ColorTurn(1);
        // OLED_ShowString(1, 1, "666");
    }
}

// #include "stm32f10x.h" // Device header
// #include "delay.h"
// #include "OLED.h"
// #include "MPU6050.h"

// //uint8_t ID;
// //int16_t AX, AY, AZ, GX, GY, GZ;

// int main()
// {
//     OLED_Init();
// //    MPU6050_Init();

// //    OLED_ShowString(1, 1, "ID:");
// //    ID = MPU6050_GetID();
// //    OLED_ShowHexNum(1, 4, ID, 2);

//     while (1)
//     {
// //        MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ); // ����6�ᴫ������ֵ
//         OLED_DrawLine(8,1,12,30,1);
//         OLED_ShowString(1, 1, "666");
//         // OLED_ShowSignedNum(2, 1, AX, 5);
//         // OLED_ShowSignedNum(3, 1, AY, 5);
//         // OLED_ShowSignedNum(4, 1, AZ, 5);
//         // OLED_ShowSignedNum(2, 8, GX, 5);
//         // OLED_ShowSignedNum(3, 8, GY, 5);
//         // OLED_ShowSignedNum(4, 8, GZ, 5);
//     }
// }
