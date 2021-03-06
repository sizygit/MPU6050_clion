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



//IIC所有操作函数
void MPU_IIC_Delay(void);				//MPU IIC延时函数
void MPU_IIC_Init(void);                //初始化IIC的IO口				 
void MPU_IIC_Start(void);				//发送IIC开始信号
void MPU_IIC_Stop(void);	  			//发送IIC停止信号
void MPU_IIC_Send_Byte(uint8_t txd);			//IIC发送一个字节
uint8_t MPU_IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
uint8_t MPU_IIC_Wait_Ack(void); 				//IIC等待ACK信号
void MPU_IIC_Ack(void);					//IIC发送ACK信号
void MPU_IIC_NAck(void);				//IIC不发送ACK信号

void IMPU_IC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t MPU_IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);
uint8_t checkDevice(uint8_t DeviceAddress);

#endif
















