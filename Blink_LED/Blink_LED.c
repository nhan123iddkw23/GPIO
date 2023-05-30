#include <stm32f10x.h>

void config() {
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); 
	  GPIO_InitTypeDef LED;
	  LED.GPIO_Mode = GPIO_Mode_Out_PP;
	  LED.GPIO_Pin = GPIO_Pin_13;
	  LED.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_Init(GPIOC,&LED);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
	  GPIO_InitTypeDef LED1;
	  LED1.GPIO_Mode = GPIO_Mode;
	  LED1.GPIO_Pin = GPIO_Pin_0;
	  LED1.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_Init(GPIOB,&LED1);
	 
	
	}

void delay() {
	   uint32_t i;
	    for(int i = 0; i < 1000000;i++);
	}

int main(void) {
	  config();
	  while(1) {
			  GPIO_ResetBits(GPIOC,GPIO_Pin_13);
			  delay();
			  GPIO_SetBits(GPIOC,GPIO_Pin_13);
			  delay();
			   GPIO_ResetBits(GPIOB,GPIO_Pin_0);
			  delay();
			  GPIO_SetBits(GPIOB,GPIO_Pin_0);
			  delay();
			}
		}