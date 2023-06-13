/*
* File: SPI.c
* Author: Hoang Minh Nhan
* Date: 13/06/2023
* Description: Day la file code SPI
*/
#include <stm32f10x.h>
#include <delay.h>

void config();
void SPI_Soft_Init();
void Clock();
void SPI_Soft_Transmit(uint8_t data);

int main() {
	 config();
	 SPI_Soft_Init();
	 Delay_ms(2000);
	 SPI_Soft_Transmit(56); //0011 1000
	}

/*
* Function: config
* Description: Ham cau hinh GPIOA
* Input:
*   none
* Output:
*   none
*/
void config() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef SPI;
	SPI.GPIO_Mode = GPIO_Mode_Out_PP;
	SPI.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	SPI.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&SPI);
}
/*
* Function: SPI_Soft_Init
* Description: Ham cau hinh SPI
* Input:
*   none
* Output:
*   none
*/
void SPI_Soft_Init() {
	  GPIO_ResetBits(GPIOA,GPIO_Pin_0); // Chan CLK, dua ve muc 0
	  GPIO_ResetBits(GPIOA,GPIO_Pin_1); // Chan MOSI, dua ve muc 0
	  GPIO_SetBits(GPIOA,GPIO_Pin_2);  // Chan SS, dua ve muc 1
	}
/*
* Function: Clock
* Description: Ham tao xung bang delay 1ms
* Input:
*   none
* Output:
*   none
*/
void Clock() {
	  GPIO_SetBits(GPIOA,GPIO_Pin_0);
	  Delay_ms(1000); // cho delay 1s de nhin thay led sang 
	  GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	  Delay_ms(1000);
	}

	/*
* Function: SPI_Soft_Transmit
* Description: Ham truyen du lieu
* Input:
*   uint8_t data: day la bien kieu uint8_t 
* Output:
*   none
*/
void SPI_Soft_Transmit(uint8_t data) {
	   GPIO_ResetBits(GPIOA,GPIO_Pin_2); // Chan ss dua ve muc 0, bat dau truyen du lieu
	       for(uint8_t i = 0; i < 8; i++) {
			       if((data&0b00000001) == 0) { //day tu bit thap den bit cao
				          GPIO_ResetBits(GPIOA,GPIO_Pin_1);
			           	Clock();
				         }
			       else {
				           GPIO_SetBits(GPIOA,GPIO_Pin_1);
				          Clock();
	           }
						 data = data>>1;
         }
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
}

