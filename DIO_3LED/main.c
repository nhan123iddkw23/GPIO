#include <stm32f10x.h>
#include <setjmp.h>

jmp_buf buf;

void config() {
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	  GPIO_InitTypeDef LED;
	  LED.GPIO_Mode = GPIO_Mode_Out_PP;
	  LED.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	  LED.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_Init(GPIOB, &LED);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	  GPIO_InitTypeDef LED1;
	  LED1.GPIO_Mode = GPIO_Mode_Out_PP;
	  LED1.GPIO_Pin = GPIO_Pin_13;
	  LED1.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_Init(GPIOC, &LED1);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	  GPIO_InitTypeDef BUTTON;
	  BUTTON.GPIO_Mode = GPIO_Mode_IPU;
	  BUTTON.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	  LED1.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_Init(GPIOA, &BUTTON);
	}

	typedef enum{
	DIO_CHANNEL_PA5,
	DIO_CHANNEL_PA6,
	DIO_CHANNEL_PA7,
	DIO_CHANNEL_PB5,
	DIO_CHANNEL_PB6,
	DIO_CHANNEL_PB7,
	DIO_CHANNEL_PC13
}Dio_ChannelType;

typedef enum{
	STD_LOW,
	STD_HIGH
}Dio_LevelType;

void Dio_WriteChannel (Dio_ChannelType ChannelId,Dio_LevelType Level);
Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId);

void delay();
void BlinkLED();
void LED();
void LED1();

int main(void) {
	  config();
	  uint8_t i;
	  i = setjmp(buf);
	  while(1) {
			if(i == 0){
			 if(Dio_ReadChannel(DIO_CHANNEL_PA5) == STD_LOW ){//
				 while(Dio_ReadChannel(DIO_CHANNEL_PA5) == STD_LOW);
				    BlinkLED();
				}
			 }
			else if(i==1){
			  if(Dio_ReadChannel(DIO_CHANNEL_PA6) == STD_LOW){//
				 while(Dio_ReadChannel(DIO_CHANNEL_PA6) == STD_LOW);
				    LED();
					 }
				}
			else if(i == 2){
			   if(Dio_ReadChannel(DIO_CHANNEL_PA7) == STD_LOW ){//
				 while(Dio_ReadChannel(DIO_CHANNEL_PA7) == STD_LOW);
					  LED1();
					}
				 }
			}
	}
			
	
	void Dio_WriteChannel (Dio_ChannelType ChannelId,Dio_LevelType Level){
	  GPIO_TypeDef * gpioPort;
	  uint16_t gpioPin;
	  switch(ChannelId) {
			case DIO_CHANNEL_PB5:
				  gpioPort = GPIOB;
			    gpioPin  = GPIO_Pin_5;
			    break;
			case DIO_CHANNEL_PB6:
				  gpioPort = GPIOB;
			    gpioPin  = GPIO_Pin_6;
			    break;
			case DIO_CHANNEL_PB7:
				  gpioPort = GPIOB;
			    gpioPin  = GPIO_Pin_7;
			    break;
			case DIO_CHANNEL_PC13:
				  gpioPort = GPIOC;
			    gpioPin  = GPIO_Pin_13;
			    break;
			}
	  if(Level == STD_LOW) {
			 GPIO_ResetBits(gpioPort,gpioPin);
			}
		else{
			GPIO_SetBits(gpioPort,gpioPin);
			}
		}

Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId) {
	    GPIO_TypeDef * gpioPort;
	    uint16_t gpioPin;
	       switch(ChannelId) {
		          case DIO_CHANNEL_PC13:
				           gpioPort = GPIOC;
			             gpioPin = GPIO_Pin_13;
			              break;
		          case DIO_CHANNEL_PB5:
				            gpioPort = GPIOB;
			              gpioPin = GPIO_Pin_5;
			              break;
							case DIO_CHANNEL_PB6:
				            gpioPort = GPIOB;
			              gpioPin = GPIO_Pin_6;
			              break;
							case DIO_CHANNEL_PB7:
				            gpioPort = GPIOB;
			              gpioPin = GPIO_Pin_7;
			              break;
							 case DIO_CHANNEL_PA5:
				            gpioPort = GPIOA;
			              gpioPin = GPIO_Pin_5;
			              break;
							case DIO_CHANNEL_PA6:
				            gpioPort = GPIOA;
			              gpioPin = GPIO_Pin_6;
			              break;
							case DIO_CHANNEL_PA7:
				            gpioPort = GPIOA;
			              gpioPin = GPIO_Pin_7;
			              break;
		}
	if(GPIO_ReadInputDataBit(gpioPort,gpioPin)==0) {
		  return STD_LOW;
		}
	else {
		  return STD_HIGH;
		}
	}



void BlinkLED() {
	  uint8_t i;
	  for(i = 0; i < 6 ; i++) {
			Dio_WriteChannel(DIO_CHANNEL_PB5,STD_HIGH);
			delay();
			Dio_WriteChannel(DIO_CHANNEL_PB5,STD_LOW);
			delay();
			Dio_WriteChannel(DIO_CHANNEL_PB6,STD_HIGH);
			delay();
			Dio_WriteChannel(DIO_CHANNEL_PB6,STD_LOW);
			delay();
			Dio_WriteChannel(DIO_CHANNEL_PB7,STD_HIGH);
			delay();
			Dio_WriteChannel(DIO_CHANNEL_PB7,STD_LOW);
			delay();
			if(Dio_ReadChannel(DIO_CHANNEL_PA6) == STD_LOW) {
				  longjmp(buf,1);
				}
			else if(Dio_ReadChannel(DIO_CHANNEL_PA7) == STD_LOW) {
				 longjmp(buf,2);
			}
			}
		}
	
void LED() {
	volatile uint8_t i;
	   for(i = 0;i<10;i++) {
			Dio_WriteChannel(DIO_CHANNEL_PB5,STD_HIGH);
			Dio_WriteChannel(DIO_CHANNEL_PB6,STD_LOW);
			Dio_WriteChannel(DIO_CHANNEL_PB7,STD_HIGH);
			 delay();
			 	if(Dio_ReadChannel(DIO_CHANNEL_PA5) == STD_LOW) {
			  longjmp(buf,0);
			}
			else if(Dio_ReadChannel(DIO_CHANNEL_PA7) == STD_LOW) {
				  longjmp(buf,2);
		    	}
			Dio_WriteChannel(DIO_CHANNEL_PB5,STD_LOW);
			Dio_WriteChannel(DIO_CHANNEL_PB6,STD_HIGH);
			Dio_WriteChannel(DIO_CHANNEL_PB7,STD_LOW);
			 delay();
			if(Dio_ReadChannel(DIO_CHANNEL_PA5) == STD_LOW) {
			  longjmp(buf,0);
			}
			else if(Dio_ReadChannel(DIO_CHANNEL_PA7) == STD_LOW) {
				  longjmp(buf,2);
		    	}
			}
	}
    
void LED1() {
	 while(1) {
			Dio_WriteChannel(DIO_CHANNEL_PB5,STD_HIGH);
			Dio_WriteChannel(DIO_CHANNEL_PB6,STD_HIGH);
			Dio_WriteChannel(DIO_CHANNEL_PB7,STD_HIGH);
     delay();
	    if(Dio_ReadChannel(DIO_CHANNEL_PA5) == STD_LOW) {
				  longjmp(buf,0);
			}
			if(Dio_ReadChannel(DIO_CHANNEL_PA6) == STD_LOW) {
				  longjmp(buf,1);
		  	}
			Dio_WriteChannel(DIO_CHANNEL_PB5,STD_LOW);
			Dio_WriteChannel(DIO_CHANNEL_PB6,STD_LOW);
			Dio_WriteChannel(DIO_CHANNEL_PB7,STD_LOW);
     delay();
	    if(Dio_ReadChannel(DIO_CHANNEL_PA5) == STD_LOW) {
				  longjmp(buf,0);
			}
		 if(Dio_ReadChannel(DIO_CHANNEL_PA6) == STD_LOW) {
				  longjmp(buf,1);
		  	}
	 }
	 }

	void delay(){
		volatile uint32_t i;
		  for(i = 0;i < 1000000;i++);
}
	

	
