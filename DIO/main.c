#include <stm32f10x.h>
#include <Dio.h>
void config() {
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); 
	  GPIO_InitTypeDef LED;
	  LED.GPIO_Mode = GPIO_Mode_Out_PP;
	  LED.GPIO_Pin = GPIO_Pin_13;
	  LED.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_Init(GPIOC,&LED);
	}

void delay1() {
	   uint32_t i;
	    for(int i = 0; i < 4000000;i++);
	}

	void delay2() {
	   uint32_t i;
	    for(int i = 0; i < 500000;i++);
	}

int main(void) {
	  config();
	  while(1) {
			  Dio_WriteChannel(DIO_CHANNEL_PC13,STD_HIGH);
			  delay2();
			  Dio_WriteChannel(DIO_CHANNEL_PC13,STD_LOW);
			  delay1();
			}
		}

	

	
		
	