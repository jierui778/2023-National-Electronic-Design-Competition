#include "iic.h"
#include "delay.h"
#include "mpu6050.h"

/**
 * @description: 初始化IIC引脚
 * @return {*}无
 */
void IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能A端口时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);            // 初始化GPIOD3,6
    GPIO_SetBits(GPIOA, GPIO_Pin_4 | GPIO_Pin_5);     // PB7,PB6 输出高
}

/**
 * @description: MPU_IIC发送起始信号
 * @return {*}无
 */
void IIC_Start(void)
{
    SDA_OUT(); // SDA线输出
    IIC_SDA = 1;
    IIC_SCL = 1;
    delay_us(2);
    IIC_SDA = 0; // START:当SCL线处于高电平时，SDA出现一个下降沿表示开始信号
    delay_us(2);
    IIC_SCL = 0; // 钳住I2C总线，准备发送或接收数据
}

/**
 * @description: MPU_IIC发送停止信号
 * @return {*}无
 */
void IIC_Stop(void)
{
    SDA_OUT(); // SDA线输出
    IIC_SCL = 0;
    IIC_SDA = 0; // STOP:当SCL线处于高电平时，SDA出现一个上升沿表示结束信号
    delay_us(2);
    IIC_SCL = 1;
    IIC_SDA = 1; // 发送I2C总线结束信号
    delay_us(2);
}

/**
 * @description: 对待应答信号
 * @return {*}1：接收应答失败  0：接收应答成功
 */
uint8_t IIC_WaitAck(void)
{
    uint8_t ucErrTime = 0;
    SDA_IN(); // SDA设置为输入
    IIC_SDA = 1;
    delay_us(2);
    IIC_SCL = 1;
    delay_us(2);
    while (READ_SDA)
    {
        ucErrTime++;
        if (ucErrTime > 250)
        {
            IIC_Stop();
            return 1;
        }
    }
    IIC_SCL = 0; // 时钟输出0
    return 0;
}
/**
 * @description: IIC产生应答信号
 * @return {*}无
 */
void IIC_SendAck(void)
{
    IIC_SCL = 0;
    SDA_OUT();
    IIC_SDA = 0;
    delay_us(2);
    IIC_SCL = 1;
    delay_us(2);
    IIC_SCL = 0;
}
/**
 * @description: IIC不产生应答信号
 * @return {*}无
 */
void IIC_NotSendAck(void)
{
    IIC_SCL = 0;
    SDA_OUT();
    IIC_SDA = 1;
    delay_us(2);
    IIC_SCL = 1;
    delay_us(2);
    IIC_SCL = 0;
}

/**
 * @description:IIC发送一个字节
 * @param {uint8_t} txd要发送的数据
 * @return {*}
 */
void IIC_SendByte(uint8_t txd)
{
    u8 t;
    SDA_OUT();
    IIC_SCL = 0; // 拉低时钟开始数据传输
    for (t = 0; t < 8; t++)
    {
        IIC_SDA = (txd & 0x80) >> 7;
        txd <<= 1;
        IIC_SCL = 1;
        delay_us(2);
        IIC_SCL = 0;
        delay_us(2);
    }
}
/**
 * @description:IIC读取一个字节
 * @param {uint8_t} ack: 1,发送ACK   0,发送NACK
 * @return {*}接收到的数据
 */
uint8_t IIC_ReadByte(uint8_t ack)
{
    unsigned char i, receive = 0;
    SDA_IN(); // SDA设置为输入
    for (i = 0; i < 8; i++)
    {
        IIC_SCL = 0;
        delay_ms(2);
        IIC_SCL = 1;
        receive <<= 1;
        if (READ_SDA)
            receive++; // 如果读到了数据
        delay_us(2);
    }
    if (!ack)
        IIC_NotSendAck(); // 发送nACK
    else
        IIC_SendAck(); // 发送ACK
    return receive;
}
