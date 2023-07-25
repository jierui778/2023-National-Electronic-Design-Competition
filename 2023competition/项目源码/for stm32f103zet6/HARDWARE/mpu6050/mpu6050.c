#include "mpu6050.h"
#include "iic.h"
#include "sys.h"

uint8_t MPU6050_Init()
{
    uint8_t res;
    IIC_Init();                                 // 初始化IIC总线
    MPU6050_WriteByte(MPU_PWR_MGMT1_REG, 0X80); // 复位MPU6050
    delay_ms(10);
    MPU6050_WriteByte(MPU_PWR_MGMT1_REG, 0X00); // 唤醒MPU6050
    MPU6050_SetGyroFsr(3);                      // 陀螺仪传感器,±2000dps
    MPU6050_SetAccelFsr(0);                     // 加速度传感器，±2g
    MPU6050_SetRate(50);                        // 设置采样率50hz
    MPU6050_WriteByte(MPU_INT_EN_REG, 0X00);    // 关闭所有中断
    MPU6050_WriteByte(MPU_USER_CTRL_REG, 0X00); // I2C主模式关闭
    MPU6050_WriteByte(MPU_FIFO_EN_REG, 0X00);   // 关闭FIFO
    MPU6050_WriteByte(MPU_INTBP_CFG_REG, 0X80); // INT引脚低电平有效

    res = MPU6050_ReadByte(MPU_DEVICE_ID_REG);
    if (res == MPU_ADDR) // 器件ID正确,即res = MPU_ADDR = 0x68
    {
        MPU6050_WriteByte(MPU_PWR_MGMT1_REG, 0X01); // 设置CLKSEL,PLL X轴为参考
        MPU6050_WriteByte(MPU_PWR_MGMT2_REG, 0X00); // 加速度与陀螺仪都工作
        MPU6050_SetRate(50);                        // 设置采样率为50Hz
    }
    else
        return 1; // 地址设置错误,返回1
//    IIC_Init();//初始化IIC总线
//	MPU6050_WriteByte(MPU_PWR_MGMT1_REG,0x00);//解除休眠状态
//	MPU6050_WriteByte(MPU_SAMPLE_RATE_REG,0x07);//陀螺仪采样率，典型值：0x07(125Hz)
//	MPU6050_WriteByte(MPU_CFG_REG,0x06);//低通滤波频率，典型值：0x06(5Hz)
//	MPU6050_WriteByte(MPU_GYRO_CFG_REG,0x18);//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
//	MPU6050_WriteByte(MPU_ACCEL_CFG_REG,0x01);//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
    return 0;     // 地址设置正确,返回0
}

/**
 * @description:设置MPU6050陀螺仪传感器满量程范围
 * @param {uint8_t} fsr:0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
 * @return {*}0,设置成功  其他,设置失败
 */
uint8_t MPU6050_SetGyroFsr(uint8_t fsr)
{
    return MPU6050_WriteByte(MPU_GYRO_CFG_REG, fsr << 3); // 设置陀螺仪满量程范围
}

/**
 * @description:设置MPU6050加速度传感器满量程范围
 * @param {uint8_t} fsr:0,±2g;1,±4g;2,±8g;3,±16g
 * @return {*}0,设置成功  其他,设置失败
 */
uint8_t MPU6050_SetAccelFsr(uint8_t fsr)
{
    return MPU6050_WriteByte(MPU_ACCEL_CFG_REG, fsr << 3); // 设置加速度传感器满量程范围
}

/**
 * @description: 设置MPU6050的数字低通滤波器
 * @param {uint16_t} lpf：数字低通滤波频率(Hz)
 * @return {*}0,设置成功  其他,设置失败
 */
uint8_t MPU6050_SetLPF(uint16_t lpf)
{
    uint8_t data = 0;
    if (lpf >= 188)
        data = 1;
    else if (lpf >= 98)
        data = 2;
    else if (lpf >= 42)
        data = 3;
    else if (lpf >= 20)
        data = 4;
    else if (lpf >= 10)
        data = 5;
    else
        data = 6;
    return MPU6050_WriteByte(MPU_CFG_REG, data); // 设置数字低通滤波器
}

uint8_t MPU6050_SetRate(uint16_t rate)
{
    uint8_t data;
    if (rate > 1000)
        rate = 1000;
    if (rate < 4)
        rate = 4;
    data = 1000 / rate - 1;
    data = MPU6050_WriteByte(MPU_SAMPLE_RATE_REG, data); // 设置数字低通滤波器
    return MPU6050_SetLPF(rate / 2);                     // 自动设置LPF为采样率的一半
}
/**
 * @description: 获取温度传感器的值
 * @return {*}温度值
 */
short MPU6050_GetTemperature(void)
{
    uint8_t buf[2];
    short raw;
    float temp;

    MPU6050_ReadLen(MPU_ADDR, MPU_TEMP_OUTH_REG, 2, buf); // 读取温度值
    raw = ((uint16_t)buf[0] << 8) | buf[1];                   // 合成数据
    temp = 36.53 + ((double)raw) / 340;                       // 转换为实际温度值
    return temp;
}


//得到陀螺仪值(原始值)
//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
uint8_t MPU6050_GetGyroscope(short *gx,short *gy,short *gz)
{
    u8 buf[6],res;  
	res=MPU6050_ReadLen(MPU_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
	if(res==0)
	{
		*gx=((u16)buf[0]<<8)|buf[1];  
		*gy=((u16)buf[2]<<8)|buf[3];  
		*gz=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}


//得到加速度值(原始值)
//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
uint8_t MPU6050_GetAccelerometer(short *ax,short *ay,short *az)
{
    u8 buf[6],res;  
	res=MPU6050_ReadLen(MPU_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
	{
		*ax=((u16)buf[0]<<8)|buf[1];  
		*ay=((u16)buf[2]<<8)|buf[3];  
		*az=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}

/**
 * @description: IIC连续写
 * @param {uint8_t} addr器件地址
 * @param {uint8_t} len数据长度
 * @param {uint8_t} *buf数据区
 * @return {*}0：成功，1：失败
 */
uint8_t MPU6050_WriteLen(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
    uint8_t i;
    IIC_Start();
    IIC_SendByte(addr << 1 | 0); // 发送器件地址+写命令，注意器件地址不包括最低位，所以左移1位，最低位为0时代表写。
    if (IIC_WaitAck())           // 等待应答
    {
        IIC_Stop();
        return 1;
    }
    IIC_SendByte(reg); // 发送寄存器地址
    IIC_WaitAck();     // 等待应答
    for (i = 0; i < len; i++)
    {
        IIC_SendByte(buf[i]); // 发送数据
        if (IIC_WaitAck())    // 等待应答
        {
            IIC_Stop();
            return 1;
        }
        {
            IIC_Stop();
            return 1;
        }
    }
    IIC_Stop();
    return 0;
}
/**
 * @description: IIC连续读
 * @param {uint8_t} addr器件地址
 * @param {uint8_t} reg寄存器地址
 * @param {uint8_t} len数据长度
 * @param {uint8_t} *buf数据区
 * @return {*}
 */
uint8_t MPU6050_ReadLen(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
    IIC_Start();
    IIC_SendByte(addr << 1 | 0); // 发送器件地址+写命令，注意器件地址不包括最低位，所以左移1位，最低位为0时代表写。
    if (IIC_WaitAck())
    {
        IIC_Stop();
        return 1;
    }
    IIC_SendByte(reg); // 发送寄存器地址
    IIC_WaitAck();     // 等待应答
    IIC_Start();
    IIC_SendByte(addr << 1 | 1); // 发送器件地址+读命令
    IIC_WaitAck();               // 等待应答
    while (len)
    {
        if (len == 1)
        {
            *buf = IIC_ReadByte(0); // 读数据,发送nACK
        }
        else
        {
            *buf = IIC_ReadByte(1); // 读数据,发送ACK
        }
        len--;
		buf++;
    }
    IIC_Stop();
    return 0;
}
/**
 * @description:
 * @param {uint8_t} reg寄存器地址
 * @param {uint8_t} data写入数据
 * @return {*}0：成功，1：失败
 */
uint8_t MPU6050_WriteByte(uint8_t reg, uint8_t data)
{
    IIC_Start();
    IIC_SendByte(MPU_ADDR << 1 | 0); // 发送器件地址+写命令
    if (IIC_WaitAck())                   // 等待应答
    {
        IIC_Stop();
        return 1;
    }
    IIC_SendByte(reg);  // 写寄存器地址
    IIC_WaitAck();      // 等待应答
    IIC_SendByte(data); // 发送数据
    if (IIC_WaitAck())  // 等待应答
    {
        IIC_Stop();
        return 1;
    }
    IIC_Stop();
    return 0;
}
uint8_t MPU6050_ReadByte(uint8_t reg)
{
    uint8_t res;
    IIC_Start();
    IIC_SendByte(MPU_ADDR << 1 | 0); // 发送器件地址+写命令
    IIC_WaitAck();                       // 等待应答
    IIC_SendByte(reg);                   // 写寄存器地址
    IIC_WaitAck();                       // 等待应答
    IIC_Start();
    IIC_SendByte(MPU_ADDR << 1 | 1); // 发送器件地址+读命令
    IIC_WaitAck();                       // 等待应答
    res = IIC_ReadByte(0);               // 读取数据,发送nACK
    IIC_Stop();                          // 产生一个停止条件
    return res;
}
