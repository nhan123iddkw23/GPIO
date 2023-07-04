#include <stm32f10x.h>
#include <stdbool.h>
#include <delay.h>

uint8_t address = 0x32;
uint8_t data = 0x00;
bool check = 0;
uint8_t ADDRESS = 0x00;
void config();
void SDA_INPUT();
void SDA_OUTPUT();
void Read_Address();
bool Read_Write();
void Check_Address();
void Read_data();
uint8_t ACK_NACK();
uint8_t a = 0;

int main() {
	 config();
	 SDA_INPUT();
	 while(1) {
		 while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0);
			 //Delay_ms(5);
			 //while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 1);
			 while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 0);
			 	Read_Address();
			 if(Read_Write() == 0) {
			  Check_Address();
			 while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 0);
			 SDA_INPUT();
		    }
		   Read_data();
			if(ACK_NACK() == 0)  {
				SDA_OUTPUT();
				GPIO_SetBits(GPIOA,GPIO_Pin_0);
				SDA_INPUT();
		      }
		   }
	   }
	

void config() {
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	 GPIO_InitTypeDef CLOCK;
	 CLOCK.GPIO_Mode =GPIO_Mode_IPU;
	 CLOCK.GPIO_Pin = GPIO_Pin_1;
	 CLOCK.GPIO_Speed = GPIO_Speed_2MHz;
	 GPIO_Init(GPIOA,&CLOCK);
}


void SDA_INPUT() {
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	 GPIO_InitTypeDef SDA;
	 SDA.GPIO_Mode =GPIO_Mode_IPU;
	 SDA.GPIO_Pin = GPIO_Pin_0;
	 SDA.GPIO_Speed = GPIO_Speed_2MHz;
	 GPIO_Init(GPIOA,&SDA);
}

void SDA_OUTPUT() {
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	 GPIO_InitTypeDef SDA;
	 SDA.GPIO_Mode =GPIO_Mode_Out_PP;
	 SDA.GPIO_Pin = GPIO_Pin_0;
	 SDA.GPIO_Speed = GPIO_Speed_2MHz;
	 GPIO_Init(GPIOA,&SDA);
}

void Read_Address() {
	 //while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 1);
	 uint8_t x = 0;
	  while(x<8) {
			 if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 1) { // doc clk
				 while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 1); // cho clk
				 check = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);  // doc data
					x++;
				 ADDRESS = ADDRESS << 1;
			   ADDRESS = ADDRESS|check;
			}
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 0);
		}
	}

bool Read_Write() {
	 //if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 1) { // doc clk
				 while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 1); // cho clk
		        if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0) {
							 return 0;
				}
	 else {
		       return 1;
	      }
		}
 //}

void Check_Address() {
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 1); // cho clk
				  if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 0) {
	if(address != ADDRESS) {
		 SDA_OUTPUT();
		 GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	}
	else {
		 SDA_OUTPUT();
		 GPIO_SetBits(GPIOA,GPIO_Pin_0);
	      }
     }
	}	

uint8_t ACK_NACK() {
	   if(data != 0) {
			 return 0;
		 }
		 else {
			 return 1;
		 }
	 }

void Read_data() {
	uint8_t x = 0;
	  while(x<8) {
			 if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 1) { // doc clk
				 while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 1); // cho clk
				  if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0) { // doc data
				  check = 0;
			 }
				else{
					check = 1;
				}
			}
			 data = data << 1;
			 data = data | check;
			 while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 0);
		}
	}

//void Check_data() {
	
	  

	
	  
