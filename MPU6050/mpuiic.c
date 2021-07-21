#include "mpuiic.h"
#include "delay.h"

 
 
 //MPU IIC 延时函数
void MPU_IIC_Delay(void)
{
	delay_us(2);
}

//初始化IIC
void MPU_IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;         //引脚配置为开漏输出
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


    MPU_IIC_Stop();          //保证IIC开始时SDA和SCL引脚都为高电平

    /* I2C1 clock enable */
    //__HAL_RCC_I2C1_CLK_ENABLE();
}
//产生IIC起始信号
void MPU_IIC_Start(void)
{
	//MPU_SDA_OUT();     //sda线输出
	SDA_H;	  	  
	SCL_H;
	MPU_IIC_Delay();
 	SDA_L;//START:when CLK is high,DATA change form high to low 
	MPU_IIC_Delay();
	SCL_L;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void MPU_IIC_Stop(void)
{
	//MPU_SDA_OUT();//sda线输出
	SCL_L;
	SDA_L;//STOP:when CLK is high DATA change form low to high
 	MPU_IIC_Delay();
	SCL_H; 
	SDA_H;//发送I2C总线结束信号
	MPU_IIC_Delay();							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t MPU_IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	//MPU_SDA_IN();      //SDA设置为输入
	SDA_H;MPU_IIC_Delay();	   
	SCL_H;MPU_IIC_Delay();	 
	while(SDA_read)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			MPU_IIC_Stop();
			return 1;
		}
	}
	SCL_L;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void MPU_IIC_Ack(void)
{
	SCL_L;
	//MPU_SDA_OUT();
	SDA_L;
	MPU_IIC_Delay();
	SCL_H;
	MPU_IIC_Delay();
	SCL_L;
}
//不产生ACK应答		    
void MPU_IIC_NAck(void)
{
	SCL_L;
	//MPU_SDA_OUT();
	SDA_H;
	MPU_IIC_Delay();
	SCL_H;
	MPU_IIC_Delay();
	SCL_L;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void MPU_IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	//MPU_SDA_OUT();
    SCL_L;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {
       if((txd&0x80)>>7 == 1)
           SDA_H;
       else
           SDA_L;
        txd<<=1; 	  
		    SCL_H;
		    MPU_IIC_Delay(); 
		    SCL_L;	
		    MPU_IIC_Delay();
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uint8_t MPU_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	//MPU_SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        SCL_L; 
        MPU_IIC_Delay();
		SCL_H;
        receive<<=1;
        if(SDA_read)receive++;
		MPU_IIC_Delay(); 
    }					 
    if (!ack)
        MPU_IIC_NAck();//发送nACK
    else
        MPU_IIC_Ack(); //发送ACK   
    return receive;
}


























