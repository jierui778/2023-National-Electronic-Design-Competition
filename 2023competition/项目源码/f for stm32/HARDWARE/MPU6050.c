//˵��:����ʹ�õ���PB10��11������
//����������ģ�⣬ȡ��������Ҳ����
//MPU6050_GetData���������������δ���������
//�޸�MPU6050_GYRO_CONFIG��  MPU6050_ACCEL_CONFIG  �޸�����
//��Ӧ��ֵΪ����ʾֵ*����/65536 


#include "stm32f10x.h"                  // Device header
#include "MPU6050.h"
#include "delay.h"

#define MPU6050_ADDRESS		0xD0

#define	MPU6050_SMPLRT_DIV		0x19
#define	MPU6050_CONFIG			0x1A
#define	MPU6050_GYRO_CONFIG		0x1B
#define	MPU6050_ACCEL_CONFIG	0x1C

#define	MPU6050_ACCEL_XOUT_H	0x3B
#define	MPU6050_ACCEL_XOUT_L	0x3C
#define	MPU6050_ACCEL_YOUT_H	0x3D
#define	MPU6050_ACCEL_YOUT_L	0x3E
#define	MPU6050_ACCEL_ZOUT_H	0x3F
#define	MPU6050_ACCEL_ZOUT_L	0x40
#define	MPU6050_TEMP_OUT_H		0x41
#define	MPU6050_TEMP_OUT_L		0x42
#define	MPU6050_GYRO_XOUT_H		0x43
#define	MPU6050_GYRO_XOUT_L		0x44
#define	MPU6050_GYRO_YOUT_H		0x45
#define	MPU6050_GYRO_YOUT_L		0x46
#define	MPU6050_GYRO_ZOUT_H		0x47
#define	MPU6050_GYRO_ZOUT_L		0x48

#define	MPU6050_PWR_MGMT_1		0x6B
#define	MPU6050_PWR_MGMT_2		0x6C
#define	MPU6050_WHO_AM_I		0x75


//IIC
void MPU6050_I2C_W_SCL(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_10, (BitAction)BitValue);
	Delay_us(10);
}

void MPU6050_I2C_W_SDA(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction)BitValue);
	Delay_us(10);
}

uint8_t MPU6050_I2C_R_SDA(void)
{
	uint8_t BitValue;
	BitValue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
	Delay_us(10);
	return BitValue;
}

void MPU6050_I2C_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);
}

void MPU6050_I2C_Start(void)
{
	MPU6050_I2C_W_SDA(1);
	MPU6050_I2C_W_SCL(1);
	MPU6050_I2C_W_SDA(0);
	MPU6050_I2C_W_SCL(0);
}

void MPU6050_I2C_Stop(void)
{
	MPU6050_I2C_W_SDA(0);
	MPU6050_I2C_W_SCL(1);
	MPU6050_I2C_W_SDA(1);
}

void MPU6050_I2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i ++)
	{
		MPU6050_I2C_W_SDA(Byte & (0x80 >> i));
		MPU6050_I2C_W_SCL(1);
		MPU6050_I2C_W_SCL(0);
	}
}

uint8_t MPU6050_I2C_ReceiveByte(void)
{
	uint8_t i, Byte = 0x00;
	MPU6050_I2C_W_SDA(1);
	for (i = 0; i < 8; i ++)
	{
		MPU6050_I2C_W_SCL(1);
		if (MPU6050_I2C_R_SDA() == 1){Byte |= (0x80 >> i);}
		MPU6050_I2C_W_SCL(0);
	}
	return Byte;
}

void MPU6050_I2C_SendAck(uint8_t AckBit)
{
	MPU6050_I2C_W_SDA(AckBit);
	MPU6050_I2C_W_SCL(1);
	MPU6050_I2C_W_SCL(0);
}

uint8_t MPU6050_I2C_ReceiveAck(void)
{
	uint8_t AckBit;
	MPU6050_I2C_W_SDA(1);
	MPU6050_I2C_W_SCL(1);
	AckBit = MPU6050_I2C_R_SDA();
	MPU6050_I2C_W_SCL(0);
	return AckBit;
}





//MPU6050
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{
	MPU6050_I2C_Start();
	MPU6050_I2C_SendByte(MPU6050_ADDRESS);
	MPU6050_I2C_ReceiveAck();
	MPU6050_I2C_SendByte(RegAddress);
	MPU6050_I2C_ReceiveAck();
	MPU6050_I2C_SendByte(Data);
	MPU6050_I2C_ReceiveAck();
	MPU6050_I2C_Stop();
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	uint8_t Data;
	
	MPU6050_I2C_Start();
	MPU6050_I2C_SendByte(MPU6050_ADDRESS);
	MPU6050_I2C_ReceiveAck();
	MPU6050_I2C_SendByte(RegAddress);
	MPU6050_I2C_ReceiveAck();
	
	MPU6050_I2C_Start();
	MPU6050_I2C_SendByte(MPU6050_ADDRESS | 0x01);
	MPU6050_I2C_ReceiveAck();
	Data = MPU6050_I2C_ReceiveByte();
	MPU6050_I2C_SendAck(1);
	MPU6050_I2C_Stop();
	
	return Data;
}

void MPU6050_Init(void)
{
	MPU6050_I2C_Init();
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);
}

uint8_t MPU6050_GetID(void)
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
						int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
	uint8_t DataH, DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*AccX = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*GyroX = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*GyroZ = (DataH << 8) | DataL;
}
