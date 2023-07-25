#include "stm32f10x.h"
#include "OLED_Font.h"
#include "OLED.h"
#include "math.h"

uint8_t OLED_GRAM[144][8];

///*引脚初始化*/
//void OLED_I2C_Init(void)
//{
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//	
//	GPIO_InitTypeDef GPIO_InitStructure;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	
////	OLED_W_SCL(1);
////	OLED_W_SDA(1);
//	//软件模拟IIC
//}

/**
  * @brief  IIC启动信号
  * @param  无
  * @retval 无
  */
void OLED_I2C_Start(void)
{
	OLED_SDA_Set();
	OLED_SCL_Set();

	OLED_SDA_Clr();

	OLED_SCL_Clr();

}

/**
  * @brief  I2C停止信号
  * @param  无
  * @retval 无
  */
void OLED_I2C_Stop(void)
{
	OLED_SDA_Clr();
	OLED_SCL_Set();
	OLED_SDA_Set();
}

/**
  * @brief  I2C等待信号响应
  * @param  无
  * @retval 无
  */
void OLED_I2C_WaitAck(void)
{
	OLED_SDA_Set();

	OLED_SCL_Set();

	OLED_SCL_Clr();

}
/**
  * @brief  I2C发送一个字节
  * @param  Byte 要发送的一个字节
  * @retval 无
  */
void OLED_I2C_SendByte(uint8_t dat)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		if(dat&0x80)//将dat的8位从最高位依次写入
		{
			OLED_SDA_Set();
    }
		else
		{
			OLED_SDA_Clr();
    }

		OLED_SCL_Set();
		OLED_SCL_Clr();//将时钟信号设置为低电平
		dat<<=1;
  }
}

/**
  * @brief  OLED写命令
  * @param  Command 要写入的命令
  * @retval 无
  */
void OLED_I2C_WriteByte(uint8_t dat,u8 mode)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//发送从机地址
	OLED_I2C_WaitAck();
	if(mode)
	{
		OLED_I2C_SendByte(0x40);	//写数据
	}
	else
	{
		OLED_I2C_SendByte(0x00);	//写命令
	}
	OLED_I2C_WaitAck();
	OLED_I2C_SendByte(dat); 
	OLED_I2C_WaitAck();
	OLED_I2C_Stop();
}
//开启OLED显示
void OLED_Display_On(void)
{
	OLED_I2C_WriteByte(0x8D,OLED_CMD); //电荷泵使能
	OLED_I2C_WriteByte(0x14,OLED_CMD); //开启电荷泵
	OLED_I2C_WriteByte(0xAF,OLED_CMD); //点亮屏幕
}
//关闭OLED显示
void OLED_Display_Off(void)
{
	OLED_I2C_WriteByte(0x8D,OLED_CMD); //电荷泵使能
	OLED_I2C_WriteByte(0x10,OLED_CMD); //关闭电荷泵
	OLED_I2C_WriteByte(0xAE,OLED_CMD); //关闭屏幕
}
//更新显存到LCD
void OLED_Refresh(void)
{
	uint8_t i,j;
	for(i=0;i<8;i++)
	{
		OLED_I2C_WriteByte(0xB0+i,OLED_CMD);	//设置页地址（0~7）
		OLED_I2C_WriteByte(0x00,OLED_CMD);		//设置显示位置—列低地址
		OLED_I2C_WriteByte(0x10,OLED_CMD);		//设置显示位置—列高地址 
        OLED_I2C_Start();
        OLED_I2C_SendByte(0x78);
        OLED_I2C_WaitAck();
        OLED_I2C_SendByte(0x40);
        OLED_I2C_WaitAck();
		for(j=0;j<128;j++)
        {
			OLED_I2C_WriteByte(OLED_GRAM[j][i],OLED_DATA);
            OLED_I2C_WaitAck();
        }
        OLED_I2C_Stop();
	}
}
/**
  * @brief  OLED清屏
  * @param  无
  * @retval 无
  */
void OLED_Clear(void)
{  
	uint8_t i, j;
	for (i= 0; i < 8; i++)
	{
		for(j = 0; j < 128; j++)
		{
			OLED_GRAM[i][j]=0;//清除所有数据
		}
	}
	OLED_Refresh();
}
/**
  * @brief  OLED设置光标位置
  * @param  Y 以左上角为原点，向下方向的坐标，范围：0~7
  * @param  X 以左上角为原点，向右方向的坐标，范围：0~127
  * @retval 无
  */

void OLED_ColorTurn(uint8_t i)
{
	if(i==0)
		{
			OLED_I2C_WriteByte(0xA6,OLED_CMD);//正常显示
		}
	if(i==1)
		{
			OLED_I2C_WriteByte(0xA7,OLED_CMD);//反色显示
		}
}
//OLED屏幕旋转180度
void OLED_DisplayTurn(uint8_t i)
{
	if(i==0)
		{
			OLED_I2C_WriteByte(0xC8,OLED_CMD);//正常显示
			OLED_I2C_WriteByte(0xA1,OLED_CMD);
		}
	if(i==1)
		{
			OLED_I2C_WriteByte(0xC0,OLED_CMD);//反转显示
			OLED_I2C_WriteByte(0xA0,OLED_CMD);
		}
}
//画点
//x:0~127
//y:0~63
//t:1 填充 0,清空
void OLED_DrawPoint(uint8_t x, uint8_t y,uint8_t mode)
{
	u8 i,m,n;
	i=y/8;
	m=y%8;
	n=1<<m;
	if(mode){OLED_GRAM[x][i]|=n;}
	else
	{
		OLED_GRAM[x][i]=~OLED_GRAM[x][i];
		OLED_GRAM[x][i]|=n;
		OLED_GRAM[x][i]=~OLED_GRAM[x][i];
	}
}
//画线
//x1,y1:起点坐标
//x2,y2:结束坐标
void OLED_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1;
	uRow=x1;//画线起点坐标
	uCol=y1;
	if(delta_x>0)incx=1; //设置单步方向 
	else if (delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if (delta_y==0)incy=0;//水平线 
	else {incy=-1;delta_y=-delta_x;}
	if(delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y;
	for(t=0;t<distance+1;t++)
	{
		OLED_DrawPoint(uRow,uCol,mode);//画点
		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}




void OLED_DrawCircle(uint8_t x,uint8_t y,uint8_t r,uint8_t mode)
{
	int a, b, num;
	a = 0;
	b = r;
	while(2 * b * b >= r * r)      
	{
		OLED_DrawPoint(x + a, y - b, mode);             //  第1象限  
		OLED_DrawPoint(x - a, y - b, mode);             //  第2象限  
		OLED_DrawPoint(x - a, y + b, mode);             //  第3象限  
		OLED_DrawPoint(x + a, y + b, mode);             //  第4象限  

		OLED_DrawPoint(x + b, y + a, mode);             //  第1象限  
		OLED_DrawPoint(x + b, y - a, mode);             //  第2象限  
		OLED_DrawPoint(x - b, y - a, mode);             //  第3象限  
		OLED_DrawPoint(x - b, y + a, mode);             //  第4象限  

		a++;
		num = (a * a + b * b) - r*r; //计算画的点离圆心的距离
		if(num > 0)//若离圆心的距离大于0则下一个点拉回来一个单位距离
		{
			b--;
			a--;
		}
	}
}
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr,uint8_t size1,uint8_t mode)
{
	u8 i, m, temp, size2, chr1;
	u8 x0 = x, y0 = y;
	if (size1 == 8)
		size2 = 6;
	else
		size2 = (size1 / 8 + ((size1 % 8) ? 1 : 0)) * (size1 / 2); // 得到字体一个字符对应点阵集所占的字节数
	chr1 = chr - ' ';											   // 计算偏移后的值
	for (i = 0; i < size2; i++)
	{
		if (size1 == 8)
		{
			temp = asc2_0806[chr1][i];
		} // 调用0806字体
		else if (size1 == 12)
		{
			temp = asc2_1206[chr1][i];
		} // 调用1206字体
		else if (size1 == 16)
		{
			temp = asc2_1608[chr1][i];
		} // 调用1608字体
		else if (size1 == 24)
		{
			temp = asc2_2412[chr1][i];
		} // 调用2412字体
		else
			return;
		for (m = 0; m < 8; m++)
		{
			if (temp & 0x01)
				OLED_DrawPoint(x, y, mode);
			else
				OLED_DrawPoint(x, y, !mode);
			temp >>= 1;
			y++;
		}
		x++;
		if ((size1 != 8) && ((x - x0) == size1 / 2))
		{
			x = x0;
			y0 = y0 + 8;
		}
		y = y0;
	}
}
//字体大小仍有问题
void OLED_ShowString(u8 x, u8 y, u8 *chr, u8 size1, u8 mode)
{
	while ((*chr >= ' ') && (*chr <= '~')) // 判断是不是非法字符!
	{
		OLED_ShowChar(x, y, *chr, size1, mode);
		if (size1 == 8)
			x += 6;
		else
			x += size1 / 2;
		chr++;
	}
}

// m^n
int OLED_Pow(uint8_t m, uint8_t n)
{
	int result = 1;
	while (n--)
	{
		result *= m;
	}
	return result;
}
//与中景园算法有出入
/**
  * @brief  OLED显示数字（十进制，正数）
  * @param  
  * @param  
  * @param  Number 要显示的数字，范围：0~4294967295
  * @param  Length 要显示数字的长度，范围：1~10
  * @retval 无
  */
void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t Number, uint8_t Length, uint8_t size1, uint8_t mode)
{
	uint8_t t, temp;
	uint8_t enshow = 0;
	for (t = 0; t < Length; t++)
	{
		temp = (Number / OLED_Pow(10, Length - t - 1)) % 10;
		if (enshow == 0 && t < (Length - 1))
		{
			if (temp == 0)
			{
				OLED_ShowChar(x + (size1 / 2) * t, y, ' ', size1, mode);
				continue;
			}
			else
				enshow = 1;
		}
		OLED_ShowChar(x + (size1 / 2) * t, y, temp + '0', size1, mode);
	}
}

void OLED_ShowSignedNum(uint8_t x, uint8_t y, int32_t Number, uint8_t Length,uint8_t size1,uint8_t mode)
{
//	uint32_t Number1;
//	if (Number >= 0)
//	{
//		OLED_ShowChar(x, y+size1/4,'+',8,mode);
//		Number1 = Number;
//	}
//	else
//	{
//		OLED_ShowChar(x, y+size1/4,'-',8,mode);
//		Number1 = -Number;
//	}
//    
//    OLED_ShowNum(x+8, y,Number1,Length,size1,mode);
    	uint8_t i;
	uint32_t Number1;
	if (Number >= 0)
	{
		OLED_ShowChar(x, y, '+',size1,mode);
		Number1 = Number;
	}
	else
	{
		OLED_ShowChar(x, y, '-',size1,mode);
		Number1 = -Number;
	}
	for (i = 0; i < Length; i++)							
	{
		OLED_ShowChar(x+8*i+8, y, Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0',size1,mode);
	}
    
}

void OLED_ShowChinese(uint8_t x, uint8_t y, uint8_t num,uint8_t size1,uint8_t mode)
{
	uint8_t m, temp;
	uint8_t x0 = x, y0 = y;
	uint16_t i, size3 = (size1 / 8 + ((size1 % 8) ? 1 : 0)) * size1; // 得到字体一个字符对应点阵集所占的字节数
	for (i = 0; i < size3; i++)
	{
		if (size1 == 16)
		{
			temp = Hzk1[num][i];
		} // 调用16*16字体
		else if (size1 == 24)
		{
			temp = Hzk2[num][i];
		} // 调用24*24字体
		else if (size1 == 32)
		{
			temp = Hzk3[num][i];
		} // 调用32*32字体
		else if (size1 == 64)
		{
			temp = Hzk4[num][i];
		} // 调用64*64字体
		else
			return;
		for (m = 0; m < 8; m++)
		{
			if (temp & 0x01)
				OLED_DrawPoint(x, y, mode);
			else
				OLED_DrawPoint(x, y, !mode);
			temp >>= 1;
			y++;
		}
		x++;
		if ((x - x0) == size1)
		{
			x = x0;
			y0 = y0 + 8;
		}
		y = y0;
	}
}

void OLED_ScrollDisplay(u8 num, u8 space, u8 mode)
{
	u8 i, n, t = 0, m = 0, r;
	while (1)
	{
		if (m == 0)
		{
			OLED_ShowChinese(128, 24, t, 16, mode); // 写入一个汉字保存在OLED_GRAM[][]数组中
			t++;
		}
		if (t == num)
		{
			for (r = 0; r < 16 * space; r++) // 显示间隔
			{
				for (i = 1; i < 144; i++)
				{
					for (n = 0; n < 8; n++)
					{
						OLED_GRAM[i - 1][n] = OLED_GRAM[i][n];
					}
				}
				OLED_Refresh();
			}
			t = 0;
		}
		m++;
		if (m == 16)
		{
			m = 0;
		}
		for (i = 1; i < 144; i++) // 实现左移
		{
			for (n = 0; n < 8; n++)
			{
				OLED_GRAM[i - 1][n] = OLED_GRAM[i][n];
			}
		}
		OLED_Refresh();
	}
}

// /**
//   * @brief  OLED显示字符串
//   * @param  Line 起始行位置，范围：1~4
//   * @param  Column 起始列位置，范围：1~16
//   * @param  String 要显示的字符串，范围：ASCII可见字符
//   * @retval 无
//   */
// void OLED_ShowString(uint8_t Line, uint8_t Column, char *String)
// {
// 	uint8_t i;
// 	for (i = 0; String[i] != '\0'; i++)
// 	{
// 		OLED_ShowChar(Line, Column + i, String[i]);
// 	}
// }

// /**
//   * @brief  OLED次方函数
//   * @retval 返回值等于X的Y次方
//   */
// uint32_t OLED_Pow(uint32_t X, uint32_t Y)
// {
// 	uint32_t Result = 1;
// 	while (Y--)
// 	{
// 		Result *= X;
// 	}
// 	return Result;
// }

// /**
//   * @brief  OLED显示数字（十进制，正数）
//   * @param  Line 起始行位置，范围：1~4
//   * @param  Column 起始列位置，范围：1~16
//   * @param  Number 要显示的数字，范围：0~4294967295
//   * @param  Length 要显示数字的长度，范围：1~10
//   * @retval 无
//   */
// void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
// {
// 	uint8_t i;
// 	for (i = 0; i < Length; i++)							
// 	{
// 		OLED_ShowChar(Line, Column + i, Number / OLED_Pow(10, Length - i - 1) % 10 + '0');
// 	}
// }

// /**
//   * @brief  OLED显示数字（十进制，带符号数）
//   * @param  Line 起始行位置，范围：1~4
//   * @param  Column 起始列位置，范围：1~16
//   * @param  Number 要显示的数字，范围：-2147483648~2147483647
//   * @param  Length 要显示数字的长度，范围：1~10
//   * @retval 无
//   */
// void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length)
// {
// 	uint8_t i;
// 	uint32_t Number1;
// 	if (Number >= 0)
// 	{
// 		OLED_ShowChar(Line, Column, '+');
// 		Number1 = Number;
// 	}
// 	else
// 	{
// 		OLED_ShowChar(Line, Column, '-');
// 		Number1 = -Number;
// 	}
// 	for (i = 0; i < Length; i++)							
// 	{
// 		OLED_ShowChar(Line, Column + i + 1, Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0');
// 	}
// }

// /**
//   * @brief  OLED显示数字（十六进制，正数）
//   * @param  Line 起始行位置，范围：1~4
//   * @param  Column 起始列位置，范围：1~16
//   * @param  Number 要显示的数字，范围：0~0xFFFFFFFF
//   * @param  Length 要显示数字的长度，范围：1~8
//   * @retval 无
//   */
// void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
// {
// 	uint8_t i, SingleNumber;
// 	for (i = 0; i < Length; i++)							
// 	{
// 		SingleNumber = Number / OLED_Pow(16, Length - i - 1) % 16;
// 		if (SingleNumber < 10)
// 		{
// 			OLED_ShowChar(Line, Column + i, SingleNumber + '0');
// 		}
// 		else
// 		{
// 			OLED_ShowChar(Line, Column + i, SingleNumber - 10 + 'A');
// 		}
// 	}
// }

// /**
//   * @brief  OLED显示数字（二进制，正数）
//   * @param  Line 起始行位置，范围：1~4
//   * @param  Column 起始列位置，范围：1~16
//   * @param  Number 要显示的数字，范围：0~1111 1111 1111 1111
//   * @param  Length 要显示数字的长度，范围：1~16
//   * @retval 无
//   */
// void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
// {
// 	uint8_t i;
// 	for (i = 0; i < Length; i++)							
// 	{
// 		OLED_ShowChar(Line, Column + i, Number / OLED_Pow(2, Length - i - 1) % 2 + '0');
// 	}
// }

/**
  * @brief  OLED初始化
  * @param  无
  * @retval 无
  */
void OLED_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能A端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(GPIOA, &GPIO_InitStructure);	  //初始化PA0,1
 	GPIO_SetBits(GPIOA,GPIO_Pin_6|GPIO_Pin_7);
    
    
	OLED_I2C_WriteByte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_I2C_WriteByte(0x00,OLED_CMD);//---set low column address
	OLED_I2C_WriteByte(0x10,OLED_CMD);//---set high column address
	OLED_I2C_WriteByte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_I2C_WriteByte(0x81,OLED_CMD);//--set contrast control register
	OLED_I2C_WriteByte(0xCF,OLED_CMD);// Set SEG Output Current Brightness
	OLED_I2C_WriteByte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_I2C_WriteByte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_I2C_WriteByte(0xA6,OLED_CMD);//--set normal display
	OLED_I2C_WriteByte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_I2C_WriteByte(0x3f,OLED_CMD);//--1/64 duty
	OLED_I2C_WriteByte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_I2C_WriteByte(0x00,OLED_CMD);//-not offset
	OLED_I2C_WriteByte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_I2C_WriteByte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_I2C_WriteByte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_I2C_WriteByte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_I2C_WriteByte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_I2C_WriteByte(0x12,OLED_CMD);
	OLED_I2C_WriteByte(0xDB,OLED_CMD);//--set vcomh
	OLED_I2C_WriteByte(0x30,OLED_CMD);//Set VCOM Deselect Level
	OLED_I2C_WriteByte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_I2C_WriteByte(0x02,OLED_CMD);//
	OLED_I2C_WriteByte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_I2C_WriteByte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_Clear();
	OLED_I2C_WriteByte(0xAF,OLED_CMD);
}
