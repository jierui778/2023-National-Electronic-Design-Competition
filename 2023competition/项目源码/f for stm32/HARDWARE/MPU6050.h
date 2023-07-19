
#ifndef __MPU6050_H
#define __MPU6050_H

void MPU6050_I2C_Init(void);//MPU6050的I2C初始化
void MPU6050_I2C_Start(void);//MPU6050的I2C开始
void MPU6050_I2C_Stop(void);//MPU6050的I2C停止

void MPU6050_I2C_SendByte(uint8_t Byte);//MPU6050的I2C发送一个字节

uint8_t MPU6050_I2C_ReceiveByte(void);//MPU6050的I2C接收一个字节

void MPU6050_I2C_SendAck(uint8_t AckBit);//MPU6050的I2C发送应答位

uint8_t MPU6050_I2C_ReceiveAck(void);//MPU6050的I2C接收应答位

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data);//MPU6050的I2C写入一个字节



uint8_t MPU6050_ReadReg(uint8_t RegAddress);

void MPU6050_Init(void);
uint8_t MPU6050_GetID(void);
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ,
					 int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ);
// void MPU6050_Kalman

#endif
