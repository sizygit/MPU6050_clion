#ifndef __MPUIIC_H
#define __MPUIIC_H

#include "stm32f1xx.h"


/* Private define ------------------------------------------------------------*/
#define SCL_H         GPIOB->BSRR = GPIO_PIN_6	                    /* GPIO_SetBits(GPIOB , GPIO_Pin_6)   */
#define SCL_L         GPIOB->BSRR = (uint32_t)GPIO_PIN_6 << 16u;   /* GPIO_ResetBits(GPIOB , GPIO_Pin_6) */

#define SDA_H         GPIOB->BSRR = GPIO_PIN_7	                    /* GPIO_SetBits(GPIOB , GPIO_Pin_7)   */
#define SDA_L         GPIOB->BSRR = (uint32_t)GPIO_PIN_7 << 16u;    /* GPIO_ResetBits(GPIOB , GPIO_Pin_7) */

#define SCL_read      GPIOB->IDR  & GPIO_PIN_6                      /* GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_6) */
#define SDA_read      GPIOB->IDR  & GPIO_PIN_7	                    /* GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_7) */


//IO��������	 
#define MPU_IIC_SCL    PBout(10) 		//SCL
#define MPU_IIC_SDA    PBout(11) 		//SDA	 
#define MPU_READ_SDA   PBin(11) 		//����SDA 

//IIC���в�������
void MPU_IIC_Delay(void);				//MPU IIC��ʱ����
void MPU_IIC_Init(void);                //��ʼ��IIC��IO��				 
void MPU_IIC_Start(void);				//����IIC��ʼ�ź�
void MPU_IIC_Stop(void);	  			//����IICֹͣ�ź�
void MPU_IIC_Send_Byte(uint8_t txd);			//IIC����һ���ֽ�
uint8_t MPU_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8_t MPU_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void MPU_IIC_Ack(void);					//IIC����ACK�ź�
void MPU_IIC_NAck(void);				//IIC������ACK�ź�

void IMPU_IC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t MPU_IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);	  
#endif
















