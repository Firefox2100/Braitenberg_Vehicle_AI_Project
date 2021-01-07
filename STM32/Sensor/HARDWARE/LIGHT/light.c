#include "light.h"

typedef   unsigned char BYTE;
//BYTE    BUF[8];                         //�������ݻ�����
//iic�ӿڳ�ʼ��

void Single_Write_BH1750(uchar REG_Address)
{
   IIC_Start();                  //��ʼ�ź�
   IIC_Send_Byte(BHAddWrite);   //�����豸��ַ+д�ź�
   IIC_Send_Byte(REG_Address);    //�ڲ��Ĵ�����ַ,
  //  BH1750_SendByte(REG_data);       //�ڲ��Ĵ�������,
   IIC_Stop();                   //����ֹͣ�ź�
}

void Light_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��B�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //��ʼ��GPIOD3,6
 	GPIO_SetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7);	

	Single_Write_BH1750(0x01);
}

//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//ռ��I2C����,׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//???:1,??????
//        0,??????
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA?????  
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//????0 	   
	return 0;  
} 
//??ACK??
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//???ACK??		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC??????
//????????
//1,???
//0,???			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
		SDA_OUT(); 	    
    IIC_SCL=0;//??????????
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA=1;
		else
			IIC_SDA=0;
		txd<<=1; 	  
		delay_us(2);   //?TEA5767??????????
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//?1???,ack=1?,??ACK,ack=0,??nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA?????
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//??nACK
    else
        IIC_Ack(); //??ACK   
    return receive;
}

/*************************************************************************************/
void bh_data_send(u8 command)
{
    do{
    IIC_Start();                      //iic????
    IIC_Send_Byte(BHAddWrite);       //??????
    }while(IIC_Wait_Ack());           //??????
    IIC_Send_Byte(command);          //????
    IIC_Wait_Ack();                   //??????
    IIC_Stop();                       //iic????
}

u16 bh_data_read(void)
{
	u16 buf;
	IIC_Start();                       //iic????
	IIC_Send_Byte(BHAddRead);         //??????+????
	IIC_Wait_Ack();                     //??????
	buf=IIC_Read_Byte(1);              //????
	buf=buf<<8;                        //??????????
	buf+=0x00ff&IIC_Read_Byte(0);      //??????????
	IIC_Stop();                        //?????? 
	return buf; 
}
