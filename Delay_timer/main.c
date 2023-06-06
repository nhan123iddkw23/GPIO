#include <stm32f10x.h>

void config() {
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef LED;
	LED.GPIO_Mode = GPIO_Mode_Out_PP;
	LED.GPIO_Pin = GPIO_Pin_All;
	LED.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&LED);
		 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef LED1;
	LED1.GPIO_Mode = GPIO_Mode_Out_PP;
	LED1.GPIO_Pin = GPIO_Pin_All;
	LED1.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB,&LED1);
	}

	void Init_TIMER() {
		TIM_TimeBaseInitTypeDef DELAY;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
		DELAY.TIM_CounterMode = TIM_CounterMode_Up;
		DELAY.TIM_Prescaler = 1;
		DELAY.TIM_Period = 65535;
		TIM_TimeBaseInit(TIM2,&DELAY);
		}
	
		void Delay_1ms() {
			Init_TIMER();
			TIM_Cmd(TIM2,ENABLE);
			TIM_SetCounter(TIM2,0);
			while(TIM_GetCounter(TIM2)<36000);
			TIM_Cmd(TIM2,DISABLE);
			}
		void Delay_ms(unsigned int time_ms) {
			while(time_ms--){
				Delay_1ms();
				}
			}
		
			int main() {
				config();
				Init_TIMER();
				while(1) {
					GPIO_SetBits(GPIOA,GPIO_Pin_0);
					GPIO_SetBits(GPIOB,GPIO_Pin_14);
					Delay_ms(500);
					GPIO_ResetBits(GPIOA,GPIO_Pin_0);
					GPIO_ResetBits(GPIOB,GPIO_Pin_14);
					Delay_ms(500);
					GPIO_SetBits(GPIOA,GPIO_Pin_1);
					GPIO_SetBits(GPIOB,GPIO_Pin_15);
					Delay_ms(500);
					GPIO_ResetBits(GPIOA,GPIO_Pin_1);
					GPIO_ResetBits(GPIOB,GPIO_Pin_15);
					Delay_ms(500);
					GPIO_SetBits(GPIOA,GPIO_Pin_2);
					GPIO_SetBits(GPIOB,GPIO_Pin_5);
					Delay_ms(500);
					GPIO_ResetBits(GPIOA,GPIO_Pin_2);
					GPIO_ResetBits(GPIOB,GPIO_Pin_5);
					Delay_ms(500);
					GPIO_SetBits(GPIOA,GPIO_Pin_3);
					GPIO_SetBits(GPIOB,GPIO_Pin_6);
					Delay_ms(500);
					GPIO_ResetBits(GPIOA,GPIO_Pin_3);
						GPIO_ResetBits(GPIOB,GPIO_Pin_6);
					Delay_ms(500);
					GPIO_SetBits(GPIOA,GPIO_Pin_4);
					GPIO_SetBits(GPIOB,GPIO_Pin_7);
					Delay_ms(500);
					GPIO_ResetBits(GPIOA,GPIO_Pin_4);
					GPIO_ResetBits(GPIOB,GPIO_Pin_7);
					Delay_ms(500);
					GPIO_SetBits(GPIOA,GPIO_Pin_5);
					GPIO_SetBits(GPIOB,GPIO_Pin_8);
					Delay_ms(500);
					GPIO_ResetBits(GPIOA,GPIO_Pin_5);
					GPIO_ResetBits(GPIOB,GPIO_Pin_8);
					Delay_ms(500);
					GPIO_SetBits(GPIOA,GPIO_Pin_6);
					GPIO_SetBits(GPIOB,GPIO_Pin_9);
					Delay_ms(500);
					GPIO_ResetBits(GPIOA,GPIO_Pin_6);
					GPIO_ResetBits(GPIOB,GPIO_Pin_9);
					Delay_ms(500);
					GPIO_SetBits(GPIOA,GPIO_Pin_7);
					GPIO_SetBits(GPIOB,GPIO_Pin_10);
					Delay_ms(500);
					GPIO_ResetBits(GPIOA,GPIO_Pin_7);
					GPIO_ResetBits(GPIOB,GPIO_Pin_10);
					Delay_ms(500);
					}
}
			