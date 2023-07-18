/*
 * @Author: Jierui 7584181012qq.com
 * @Date: 2023-07-18 10:19:54
 * @LastEditors: Jierui 7584181012qq.com
 * @LastEditTime: 2023-07-18 14:06:04
 * @FilePath: \2023电赛\competition\2023competition\项目源码\f for stm32\HARDWARE\MPU6050.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __MPU6050_H
#define __MPU6050_H

void MPU6050_I2C_Init(void);
void MPU6050_I2C_Start(void);
void MPU6050_I2C_Stop(void);
void MPU6050_I2C_SendByte(uint8_t Byte);
uint8_t MPU6050_I2C_ReceiveByte(void);
void MPU6050_I2C_SendAck(uint8_t AckBit);
uint8_t MPU6050_I2C_ReceiveAck(void);

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data);
uint8_t MPU6050_ReadReg(uint8_t RegAddress);

void MPU6050_Init(void);
uint8_t MPU6050_GetID(void);
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ,
					 int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ);

#endif
