#include "mpuiic.h"
#include "delay.h"

 
 
 //MPU IIC ��ʱ����
void MPU_IIC_Delay(void)
{
	delay_us(2);
}

//��ʼ��IIC
void MPU_IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;         //��������Ϊ��©���
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


    MPU_IIC_Stop();          //��֤IIC��ʼʱSDA��SCL���Ŷ�Ϊ�ߵ�ƽ

    /* I2C1 clock enable */
    //__HAL_RCC_I2C1_CLK_ENABLE();
}
//����IIC��ʼ�ź�
void MPU_IIC_Start(void)
{
	//MPU_SDA_OUT();     //sda�����
	SDA_H;	  	  
	SCL_H;
	MPU_IIC_Delay();
 	SDA_L;//START:when CLK is high,DATA change form high to low 
	MPU_IIC_Delay();
	SCL_L;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void MPU_IIC_Stop(void)
{
	//MPU_SDA_OUT();//sda�����
	SCL_L;
	SDA_L;//STOP:when CLK is high DATA change form low to high
 	MPU_IIC_Delay();
	SCL_H; 
	SDA_H;//����I2C���߽����ź�
	MPU_IIC_Delay();							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t MPU_IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	//MPU_SDA_IN();      //SDA����Ϊ����
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
	SCL_L;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
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
//������ACKӦ��		    
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
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void MPU_IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	//MPU_SDA_OUT();
    SCL_L;//����ʱ�ӿ�ʼ���ݴ���
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
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
uint8_t MPU_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	//MPU_SDA_IN();//SDA����Ϊ����
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
        MPU_IIC_NAck();//����nACK
    else
        MPU_IIC_Ack(); //����ACK   
    return receive;
}


























