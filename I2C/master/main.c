#include <stm32f10x.h>
#include <delay.h>
#include <stdbool.h>



void I2C_Data(uint8_t data);
void I2C_Start();
void I2C_Stop();
void I2C_Read();
void I2C_Write();
void Clock();
void I2C_Address(uint8_t address);
bool  ACK_NACK();
void config1();
void SDA_OUTPUT();
void SDA_INPUT();
uint8_t x = 0;
uint8_t i = 0;
uint8_t DATA = 0x00;
bool check = 0;


int main() {
	config1(1);
	SDA_OUTPUT();
	while(1){
	I2C_Start();
	I2C_Address(0x32);
	I2C_Write();
	while(1) {
		if(ACK_NACK() == 0) {
	      I2C_Data(0x38);
		}
		else {
			GPIO_SetBits(GPIOA,GPIO_Pin_2);
		}
		if(ACK_NACK() == 0) {
			I2C_Stop();
    }
		else {
			GPIO_SetBits(GPIOA,GPIO_Pin_3);
	      }
     }
	//}
}
	}
void config1() {
	 GPIO_InitTypeDef I2C;
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	 I2C.GPIO_Mode = GPIO_Mode_Out_PP;
	 I2C.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	 I2C.GPIO_Speed = GPIO_Speed_2MHz;
	 GPIO_Init(GPIOA,&I2C);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	  GPIO_InitTypeDef BUTTON;
	 BUTTON.GPIO_Mode = GPIO_Mode_IPU;
	 BUTTON.GPIO_Pin = GPIO_Pin_0;
	 I2C.GPIO_Speed = GPIO_Speed_2MHz;
	 GPIO_Init(GPIOA,&BUTTON);
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
	 GPIO_SetBits(GPIOA,GPIO_Pin_0);
   GPIO_SetBits(GPIOA,GPIO_Pin_1);	//SDA
	 Delay_ms(5);
	 GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	 Delay_ms(5);
	 GPIO_ResetBits(GPIOA,GPIO_Pin_1); //SCL
}

void I2C_Stop() {
	 if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1) == 1) { // Doc gia tri dau ra
	 GPIO_ResetBits(GPIOA,GPIO_Pin_0); //SDA
	 //Delay_ms(1);
	 GPIO_SetBits(GPIOA,GPIO_Pin_0);
	 }
}
	
void I2C_Read() {
	  GPIO_SetBits(GPIOA,GPIO_Pin_0);
	 // Delay_ms(5);
		Clock();
}

void I2C_Write() {
	  GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	  //Delay_ms(5);
		Clock();
}

void Clock() {
	  GPIO_SetBits(GPIOA,GPIO_Pin_1);
	  Delay_ms(5);
	  GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	  Delay_ms(5);
}

void I2C_Address(uint8_t address) {
	 for(i = 0 ; i < 8; i++) {
		   if((address&0x80) == 0) {
				 GPIO_ResetBits(GPIOA,GPIO_Pin_0);
				 check = 0;
			    }
			 else{
				 GPIO_SetBits(GPIOA,GPIO_Pin_0);
				 check = 1;
			 }
			 address = address << 1;
			 DATA = DATA << 1;
			 DATA = DATA| check;
			 //Delay_ms(5);
			 Clock();
		 }
	 }

bool  ACK_NACK() {
	 SDA_INPUT();
	 if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0) {
		  return 0;
	 }
	 else{
		 return 1;
	 }
	 SDA_OUTPUT();
	 //Delay_ms(5);
	 Clock();
}

void I2C_Data(uint8_t data) {
	  for(x = 0; x < 8; x++) {
			 if( (data&0x80) ==0) {
				  GPIO_ResetBits(GPIOA,GPIO_Pin_0);
			 }
			 else {
				 GPIO_SetBits(GPIOA,GPIO_Pin_0);
			 }
			 data = data << 1;
			 //Delay_ms(5);
			 Clock();
		 }
	}
	   

