#include <Dio.h>
#include <setjmp.h>

jmp_buf buf;

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
	if(GPIO_ReadInputDataBit(gpioPort,gpioPin)==Bit_SET) {
		  return STD_HIGH;
		}
	else {
		  return STD_LOW;
		}
	}



void BlinkLED(uint8_t n) {
	    uint8_t i;
	  for(i = 0; i < n ; i++) {
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
			if(Dio_ReadChannel(DIO_CHANNEL_PA6) == STD_LOW&&Dio_ReadChannel(DIO_CHANNEL_PA5) == STD_HIGH&&Dio_ReadChannel(DIO_CHANNEL_PA7) == STD_HIGH) {
				  longjmp(buf,1);
				}
			else if(Dio_ReadChannel(DIO_CHANNEL_PA7) == STD_LOW&&Dio_ReadChannel(DIO_CHANNEL_PA6) == STD_HIGH&&Dio_ReadChannel(DIO_CHANNEL_PA5) == STD_HIGH) {
				 longjmp(buf,2);
				}
			}
		}
	
void LED(uint8_t n) {
	  for(uint8_t i = 0; i < n ; i++) {
			Dio_WriteChannel(DIO_CHANNEL_PB5,STD_HIGH);
			Dio_WriteChannel(DIO_CHANNEL_PB6,STD_HIGH);
			Dio_WriteChannel(DIO_CHANNEL_PB7,STD_HIGH);
			delay();
			Dio_WriteChannel(DIO_CHANNEL_PB5,STD_LOW);
			Dio_WriteChannel(DIO_CHANNEL_PB6,STD_LOW);
			Dio_WriteChannel(DIO_CHANNEL_PB7,STD_LOW);
			if(Dio_ReadChannel(DIO_CHANNEL_PA5) == STD_LOW&&Dio_ReadChannel(DIO_CHANNEL_PA6) == STD_HIGH&&Dio_ReadChannel(DIO_CHANNEL_PA7) == STD_HIGH) {
				  longjmp(buf,0);
				}
			if(Dio_ReadChannel(DIO_CHANNEL_PA7) == STD_LOW&&Dio_ReadChannel(DIO_CHANNEL_PA6) == STD_HIGH&&Dio_ReadChannel(DIO_CHANNEL_PA5) == STD_HIGH) {
				  longjmp(buf,2);
			}
		}
	}
    
void LED1() {
			Dio_WriteChannel(DIO_CHANNEL_PB5,STD_LOW);
			Dio_WriteChannel(DIO_CHANNEL_PB6,STD_LOW);
			Dio_WriteChannel(DIO_CHANNEL_PB7,STD_LOW);
	    if(Dio_ReadChannel(DIO_CHANNEL_PA5) == STD_LOW&&Dio_ReadChannel(DIO_CHANNEL_PA6) == STD_HIGH&&Dio_ReadChannel(DIO_CHANNEL_PA7) == STD_HIGH) {
				  longjmp(buf,0);
				}
			if(Dio_ReadChannel(DIO_CHANNEL_PA6) == STD_LOW&&Dio_ReadChannel(DIO_CHANNEL_PA7) == STD_HIGH&&Dio_ReadChannel(DIO_CHANNEL_PA6) == STD_HIGH) {
				  longjmp(buf,1);
			}
	}

void program() {
	uint8_t i;
	  i = setjmp(buf);
	  while(1) {
			 if(Dio_ReadChannel(DIO_CHANNEL_PA5) == STD_LOW && i == 0 ){//
				 while(Dio_ReadChannel(DIO_CHANNEL_PA5) == STD_LOW);
				    BlinkLED(5);
				}
			 else if(Dio_ReadChannel(DIO_CHANNEL_PA6) == STD_LOW && i == 1){
				 while(Dio_ReadChannel(DIO_CHANNEL_PA6) == STD_LOW);
				    LED(6);
				 }
			  else if(Dio_ReadChannel(DIO_CHANNEL_PA7) == STD_LOW && i == 2){
				 while(Dio_ReadChannel(DIO_CHANNEL_PA7) == STD_LOW);
					  LED1();
					}	 
			}
		}

	

