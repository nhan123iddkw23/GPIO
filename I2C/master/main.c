#include <stm32f10x.h>
#include <delay.h>



void I2C_Data(uint8_t data);
void config1() {
	 GPIO_InitTypeDef I2C;
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	 I2C.GPIO_Mode = GPIO_Mode_Out_PP;
	 I2C.GPIO_Pin = GPIO_Pin_1;
	 I2C.GPIO_Speed = GPIO_Speed_2MHz;
	 GPIO_Init(GPIOA,&I2C);
}

void SDA_OUTPUT() {
		GPIO_InitTypeDef SDA;
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	 SDA.GPIO_Mode = GPIO_Mode_Out_PP;
	 SDA.GPIO_Pin = GPIO_Pin_0;
	 SDA.GPIO_Speed = GPIO_Speed_2MHz;
	 GPIO_Init(GPIOA,&SDA);
}

void SDA_INPUT() {
	 GPIO_InitTypeDef SDA;
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	 SDA.GPIO_Mode = GPIO_Mode_IPU;
	 SDA.GPIO_Pin = GPIO_Pin_0;
	 SDA.GPIO_Speed = GPIO_Speed_2MHz;
	 GPIO_Init(GPIOA,&SDA);
}

void I2C_Start() {
	 GPIO_SetBits(GPIOA,GPIO_Pin_0); //SDA
	 Delay_ms(10);
	 GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	 Delay_ms(10);
	 GPIO_ResetBits(GPIOA,GPIO_Pin_1); //SCL
}

void I2C_Stop() {
	 if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1) == 1) { // Doc gia tri dau ra
	 GPIO_ResetBits(GPIOA,GPIO_Pin_0); //SDA
	 Delay_ms(1);
	 GPIO_SetBits(GPIOA,GPIO_Pin_0);
	 }
}
	
uint8_t I2C_Read() {
	  GPIO_SetBits(GPIOA,GPIO_Pin_0);
	  return 1;
}

uint8_t I2C_Write() {
	  GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	return 0;
}

void Clock() {
	  GPIO_SetBits(GPIOA,GPIO_Pin_1);
	  Delay_ms(10);
	  GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	  Delay_ms(10);
}

void I2C_Address(uint8_t address) {
	 uint8_t i;
	 for(i = 0 ; i < 8; i++) {
		   if((address&0x80) == 0) {
				 GPIO_SetBits(GPIOA,GPIO_Pin_0);
			    }
			 else{
				 GPIO_ResetBits(GPIOA,GPIO_Pin_0);
			 }
			 address = address << 1;
			 Clock();
		 }
	 }

void  ACK_NACK() {
	 SDA_INPUT();
	 if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0) {
		  I2C_Data(1);
	 }
	 SDA_OUTPUT();
}

void I2C_Data(uint8_t data) {
	  uint8_t i;
	  for(i = 0; i < 8; i++) {
			 if( (data&0x80) ==0) {
				  GPIO_ResetBits(GPIOA,GPIO_Pin_0);
			 }
			 else {
				 GPIO_SetBits(GPIOA,GPIO_Pin_0);
			 }
			 data = data << 1;
			 Clock();
		 }
	}
	   

