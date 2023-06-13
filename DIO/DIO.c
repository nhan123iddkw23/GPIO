/*
* File: dio.c
* Author: Hoang Minh Nhan
* Date: 29/05/2023
* Description: Day la file .c
*/
#include <Dio.h>

/*
* Function: DIO_WriteChannel
* Description: Ham xuat muc 1 va 0 ra chan STM32F103C8T6
* Input:
*   ChnnelID - Day la bien Dio_ChannelType(Kieu Enum)
*   Level    - Day la bien Dio_LevelType(Kieu Enum)
* Output:
*   none
*/
void Dio_WriteChannel (Dio_ChannelType ChannelId,Dio_LevelType Level){
	  GPIO_TypeDef * gpioPort;  
	  uint16_t gpioPin; 
	   switch(ChannelId) {
			 case DIO_CHANNEL_PA0:
				 gpioPort = GPIOA;
			   gpioPin = GPIO_Pin_0;
			 break;
			 case DIO_CHANNEL_PA1:
				 gpioPort = GPIOA;
			   gpioPin = GPIO_Pin_1;
			 break;
			 case DIO_CHANNEL_PA2:
				 gpioPort = GPIOA;
			   gpioPin = GPIO_Pin_2;
			 break;
			 case DIO_CHANNEL_PA3:
				 gpioPort = GPIOA;
			   gpioPin = GPIO_Pin_3;
			 break;
			 case DIO_CHANNEL_PA4:
				 gpioPort = GPIOA;
			   gpioPin = GPIO_Pin_4;
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
			 case DIO_CHANNEL_PA8:
				 gpioPort = GPIOA;
			   gpioPin = GPIO_Pin_8;
			 break;
			 case DIO_CHANNEL_PA9:
				 gpioPort = GPIOA;
			   gpioPin = GPIO_Pin_10;
			 break;
			 case DIO_CHANNEL_PC13:
				 gpioPort = GPIOC;
			   gpioPin = GPIO_Pin_13;
			 break;
			 }
	if(Level == STD_LOW) {  
      GPIO_ResetBits(gpioPort,gpioPin); // Ham xuat muc 0 ra chan STM32F103C8T6
     }
  else {
     	GPIO_SetBits(gpioPort,gpioPin);   // Ham xuat muc 1 ra chan STM32F103C8T6
     }
}
		 
/*
* Function: DIO_ReadChannel
* Description: Ham doc muc 1 va 0 ra chan STM32F103C8T6
* Input:
*   ChnnelID - Day la bien Dio_ChannelType(Kieu Enum)
* Output:
*   STD_LOW - Tuong duong muc 0
*   STD_HIGH - Tuong duong muc 1
*/
Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId) {
	GPIO_TypeDef * gpioPort;
	uint16_t gpioPin;
	switch(ChannelId) {
		case DIO_CHANNEL_PC13:
				 gpioPort = GPIOC;
			   gpioPin = GPIO_Pin_13;
			 break;
		}
	if(GPIO_ReadInputDataBit(gpioPort,gpioPin) == 0) {  //Ham doc muc logic dau vao 1 hoac 0
		  return STD_LOW;
		}
	else {
		  return STD_HIGH;
		}
	}

	