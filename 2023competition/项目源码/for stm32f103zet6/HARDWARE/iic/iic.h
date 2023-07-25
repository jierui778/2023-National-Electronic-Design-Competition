#ifndef __IIC_H
#define __IIC_H
#include "sys.h"
#include "delay.h"

	   		   
//IO方向设置
#define SDA_IN()  {GPIOA->CRL&=0XFF0FFFFF;GPIOA->CRL|=8<<20;} 
#define SDA_OUT() {GPIOA->CRL&=0XFF0FFFFF;GPIOA->CRL|=3<<20;}

// IO操作函数
#define IIC_SCL PAout(4) // SCL
#define IIC_SDA PAout(5) // SDA
#define READ_SDA PAin(5) // 输入SDA PB2

void IIC_Init(void);//初始化IIC的IO口

void IIC_Start(void);//发送IIC开始信号
void IIC_Stop(void);//发送IIC停止信号

void IIC_SendByte(uint8_t txd);//IIC发送一个字节
uint8_t IIC_ReadByte(unsigned char ack);//IIC读取一个字节

uint8_t IIC_WaitAck(void);//IIC等待ACK信号

void IIC_SendAck(void);//IIC发送ACK信号
void IIC_NotSendAck(void);//IIC不发送ACK信号


#endif
