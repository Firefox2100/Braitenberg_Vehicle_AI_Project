#ifndef __LIGHT_H
#define __LIGHT_H
#include "sys.h"
#include "delay.h"
//IO��������

#define SDA_IN()  {GPIOD->CRL&=0X0FFFFFFF;GPIOD->CRL|=(u32)8<<28;}
#define SDA_OUT() {GPIOD->CRL&=0X0FFFFFFF;GPIOD->CRL|=(u32)3<<28;}



#define IIC_SCL    PDout(6) //SCL
#define IIC_SDA    PDout(7) //SDA	 
#define READ_SDA   PDin(7)  //??SDA 
#define ADDR 0x23//0100011
#define uchar unsigned char 

#define BHAddWrite     0x46      //�ӻ���ַ+���д����λ
#define BHAddRead      0x47      //�ӻ���ַ+��������λ
#define BHPowDown      0x00      //�ر�ģ��
#define BHPowOn        0x01      //��ģ��ȴ�����ָ��
#define BHReset        0x07      //�������ݼĴ���ֻ��PowerOnģʽ����Ч
#define BHModeH1       0x10      //�߷ֱ��� ��λ1lx ����ʱ��120ms
#define BHModeH2       0x11      //�߷ֱ���ģʽ2 ��λ0.5lx ����ʱ��120ms
#define BHModeL        0x13      //�ͷֱ��� ��λ4lx ����ʱ��16ms
#define BHSigModeH     0x20      //һ�θ߷ֱ��� ���� ������ģ��ת�� PowerDownģʽ
#define BHSigModeH2    0x21      //ͬ������
#define BHSigModeL     0x23      //ͬ������

void Single_Write_BH1750(uchar REG_Address);
void Light_Init(void);
void bh_data_send(u8 command);
u16 bh_data_read(void);

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	

#endif