#include <stm32f10x.h>
#include <delay.h>

typedef struct {
	uint16_t  SPI_BaudRatePrescaler;
	uint16_t  SPI_CPHA;
	uint16_t  SPI_CPOL ;
	uint16_t  SPI_CRCPolynomial ;
	uint16_t  SPI_DataSize ;
	uint16_t  SPI_Direction ;
	uint16_t  SPI_FirstBit ;
	uint16_t  SPI_Mode ;
	uint16_t  SPI_NSS ;
}Spi_ConfigType;

typedef uint8_t Std_ReturnType;
typedef uint8_t Spi_ChannelType;
typedef uint8_t Spi_DataBufferType;


#define spi2 (Spi_ChannelType)2
#define E_OK (Std_ReturnType)0
#define E_NOT_OK (Std_ReturnType)1

void config_GPIOC() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	 GPIO_InitTypeDef gpioc; 
	 gpioc.GPIO_Mode = GPIO_Mode_Out_PP;
	 gpioc.GPIO_Pin = GPIO_Pin_13;
	 gpioc.GPIO_Speed = GPIO_Speed_2MHz;
	 GPIO_Init(GPIOC,&gpioc);
}

void config_GPIOA() {
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	 GPIO_InitTypeDef gpioa; 
	 gpioa.GPIO_Mode = GPIO_Mode_Out_PP;
	 gpioa.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_7;
	 gpioa.GPIO_Speed = GPIO_Speed_2MHz;
	 GPIO_Init(GPIOA,&gpioa);
	
	 gpioa.GPIO_Mode = GPIO_Mode_IPU;
	 gpioa.GPIO_Pin = GPIO_Pin_6;
	 gpioa.GPIO_Speed = GPIO_Speed_2MHz;
	 GPIO_Init(GPIOA,&gpioa);
}

void config_GPIOB() {
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	  // CS
	 GPIO_InitTypeDef gpiob; 
	 gpiob.GPIO_Mode = GPIO_Mode_AF_PP;
	 gpiob.GPIO_Pin = GPIO_Pin_12;
	 gpiob.GPIO_Speed = GPIO_Speed_2MHz;
	 GPIO_Init(GPIOB,&gpiob);
	  // CLK
	 gpiob.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	 gpiob.GPIO_Pin = GPIO_Pin_13;
	 gpiob.GPIO_Speed = GPIO_Speed_2MHz;
	 GPIO_Init(GPIOB,&gpiob);
	 // MOSI
	 gpiob.GPIO_Mode = GPIO_Mode_AF_PP;
	 gpiob.GPIO_Pin = GPIO_Pin_14;
	 gpiob.GPIO_Speed = GPIO_Speed_2MHz;
	 GPIO_Init(GPIOB,&gpiob);
	 // MISO 
	 gpiob.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	 gpiob.GPIO_Pin = GPIO_Pin_13;
	 gpiob.GPIO_Speed = GPIO_Speed_2MHz;
	 GPIO_Init(GPIOB,&gpiob);
}


void Spi_Init () { //const
	  Spi_ConfigType* ConfigPtr;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	  ConfigPtr->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	  ConfigPtr->SPI_CPHA = SPI_CPHA_1Edge;
	  ConfigPtr->SPI_CPOL = SPI_CPOL_High;
	  ConfigPtr->SPI_DataSize = SPI_DataSize_8b;
	  ConfigPtr->SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	  ConfigPtr->SPI_FirstBit = SPI_FirstBit_MSB;
	  ConfigPtr->SPI_Mode = SPI_Mode_Slave;
	  ConfigPtr->SPI_NSS = SPI_NSS_Soft;
	  SPI_Init(SPI2,&ConfigPtr);
	  SPI_Cmd(SPI2,ENABLE);
}

Std_ReturnType Spi_DeInit (void) {
	SPI_Cmd(SPI2,DISABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,DISABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,DISABLE);
	return E_OK;
	}
	


	uint8_t data= 0x00	;

typedef enum{
	DIO_CHANNEL_PA0,
	DIO_CHANNEL_PA1,
	DIO_CHANNEL_PA2,
	DIO_CHANNEL_PA3,
	DIO_CHANNEL_PA4,
	DIO_CHANNEL_PA5,
	DIO_CHANNEL_PA6,
	DIO_CHANNEL_PA7,
	DIO_CHANNEL_PA8,
	DIO_CHANNEL_PA9,
	DIO_CHANNEL_PA10,
	DIO_CHANNEL_PA11,
	DIO_CHANNEL_PA12,
	DIO_CHANNEL_PA13,
	DIO_CHANNEL_PA14,
	DIO_CHANNEL_PA15,
	DIO_CHANNEL_PB0,
	DIO_CHANNEL_PB1,
	DIO_CHANNEL_PB2,
	DIO_CHANNEL_PB3,
	DIO_CHANNEL_PB4,
	DIO_CHANNEL_PB5,
	DIO_CHANNEL_PB6,
	DIO_CHANNEL_PB7,
	DIO_CHANNEL_PB8,
	DIO_CHANNEL_PB9,
	DIO_CHANNEL_PB10,
	DIO_CHANNEL_PB11,
	DIO_CHANNEL_PB12,
	DIO_CHANNEL_PB13,
	DIO_CHANNEL_PB14,
	DIO_CHANNEL_PB15,
	DIO_CHANNEL_PC13,
	DIO_CHANNEL_PC14,
	DIO_CHANNEL_PC15
}Dio_ChannelType;

typedef enum{
	STD_LOW,
	STD_HIGH
}Dio_LevelType;

		
void Dio_WriteChannel (Dio_ChannelType ChannelId,Dio_LevelType Level) {
	   GPIO_TypeDef* gpio;
	   uint16_t gpioPin;
	   switch(ChannelId) {
			 case DIO_CHANNEL_PA0:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_0;
				 break;
			 }
			 case DIO_CHANNEL_PA1:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_1;
				 break;
			 }
			 case DIO_CHANNEL_PA2:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_2;
				 break;
			 }
			 case DIO_CHANNEL_PA3:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_3;
				 break;
			 }
			 case DIO_CHANNEL_PA4:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_4;
				 break;
			 }
			 case DIO_CHANNEL_PA5:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_5;
				 break;
			 }
			 case DIO_CHANNEL_PA6:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_6;
				 break;
			 }
			 case DIO_CHANNEL_PA7:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_7;
				 break;
			 }
			 case DIO_CHANNEL_PA8:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_8;
				 break;
			 }
			 case DIO_CHANNEL_PA9:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_9;
				 break;
			 }
			 case DIO_CHANNEL_PA10:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_10;
				 break;
			 }
			 case DIO_CHANNEL_PA11:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_11;
				 break;
			 }
			 case DIO_CHANNEL_PA12:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_12;
				 break;
			 }
			 case DIO_CHANNEL_PA13:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_13;
				 break;
			 }
			 case DIO_CHANNEL_PA14:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_14;
				 break;
			 }
			 case DIO_CHANNEL_PA15:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_15;
				 break;
			 }
			 case DIO_CHANNEL_PB0:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_0;
				 break;
			 }
			 case DIO_CHANNEL_PB1:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_1;
				 break;
			 }
			 case DIO_CHANNEL_PB2:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_2;
				 break;
			 }
			 case DIO_CHANNEL_PB3:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_3;
				 break;
			 }
			 case DIO_CHANNEL_PB4:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_4;
				 break;
			 }
			 case DIO_CHANNEL_PB5:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_5;
				 break;
			 }
			 case DIO_CHANNEL_PB6:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_6;
				 break;
			 }
			 case DIO_CHANNEL_PB7:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_7;
				 break;
			 }
			 case DIO_CHANNEL_PB8:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_8;
				 break;
			 }
			 case DIO_CHANNEL_PB9:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_9;
				 break;
			 }
			 case DIO_CHANNEL_PB10:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_10;
				 break;
			 }
			 case DIO_CHANNEL_PB11:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_11;
				 break;
			 }
			 case DIO_CHANNEL_PB12:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_12;
				 break;
			 }
			 case DIO_CHANNEL_PB13:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_13;
				 break;
			 }
			 case DIO_CHANNEL_PB14:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_14;
				 break;
			 }
			 case DIO_CHANNEL_PB15:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_15;
				 break;
			 }
			 
			 case DIO_CHANNEL_PC13:
			 {
				 gpio = GPIOC;
				 gpioPin = GPIO_Pin_13;
				 break;
			 }
			 case DIO_CHANNEL_PC14:
			 {
				 gpio = GPIOC;
				 gpioPin = GPIO_Pin_14;
				 break;
			 }
			 case DIO_CHANNEL_PC15:
			 {
				 gpio = GPIOC;
				 gpioPin = GPIO_Pin_15;
				 break;
			 }
		 }
		 if(Level == STD_HIGH) {
			 GPIO_SetBits(gpio,gpioPin);
		 }
		 else{
			 GPIO_ResetBits(gpio,gpioPin);
		 }		 
}

Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId) {
	   GPIO_TypeDef* gpio;
	   uint16_t gpioPin;
	   switch(ChannelId) {
			 case DIO_CHANNEL_PA0:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_0;
				 break;
			 }
			 case DIO_CHANNEL_PA1:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_1;
				 break;
			 }
			 case DIO_CHANNEL_PA2:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_2;
				 break;
			 }
			 case DIO_CHANNEL_PA3:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_3;
				 break;
			 }
			 case DIO_CHANNEL_PA4:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_4;
				 break;
			 }
			 case DIO_CHANNEL_PA5:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_5;
				 break;
			 }
			 case DIO_CHANNEL_PA6:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_6;
				 break;
			 }
			 case DIO_CHANNEL_PA7:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_7;
				 break;
			 }
			 case DIO_CHANNEL_PA8:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_8;
				 break;
			 }
			 case DIO_CHANNEL_PA9:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_9;
				 break;
			 }
			 case DIO_CHANNEL_PA10:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_10;
				 break;
			 }
			 case DIO_CHANNEL_PA11:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_11;
				 break;
			 }
			 case DIO_CHANNEL_PA12:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_12;
				 break;
			 }
			 case DIO_CHANNEL_PA13:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_13;
				 break;
			 }
			 case DIO_CHANNEL_PA14:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_14;
				 break;
			 }
			 case DIO_CHANNEL_PA15:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_15;
				 break;
			 }
			 case DIO_CHANNEL_PB0:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_0;
				 break;
			 }
			 case DIO_CHANNEL_PB1:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_1;
				 break;
			 }
			 case DIO_CHANNEL_PB2:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_2;
				 break;
			 }
			 case DIO_CHANNEL_PB3:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_3;
				 break;
			 }
			 case DIO_CHANNEL_PB4:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_4;
				 break;
			 }
			 case DIO_CHANNEL_PB5:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_5;
				 break;
			 }
			 case DIO_CHANNEL_PB6:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_6;
				 break;
			 }
			 case DIO_CHANNEL_PB7:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_7;
				 break;
			 }
			 case DIO_CHANNEL_PB8:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_8;
				 break;
			 }
			 case DIO_CHANNEL_PB9:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_9;
				 break;
			 }
			 case DIO_CHANNEL_PB10:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_10;
				 break;
			 }
			 case DIO_CHANNEL_PB11:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_11;
				 break;
			 }
			 case DIO_CHANNEL_PB12:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_12;
				 break;
			 }
			 case DIO_CHANNEL_PB13:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_13;
				 break;
			 }
			 case DIO_CHANNEL_PB14:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_14;
				 break;
			 }
			 case DIO_CHANNEL_PB15:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_15;
				 break;
			 }
			 
			 case DIO_CHANNEL_PC13:
			 {
				 gpio = GPIOC;
				 gpioPin = GPIO_Pin_13;
				 break;
			 }
			 case DIO_CHANNEL_PC14:
			 {
				 gpio = GPIOC;
				 gpioPin = GPIO_Pin_14;
				 break;
			 }
			 case DIO_CHANNEL_PC15:
			 {
				 gpio = GPIOC;
				 gpioPin = GPIO_Pin_15;
				 break;
			 }
		 }
		 if(GPIO_ReadInputDataBit(gpio,gpioPin) == 0) {
			 return STD_HIGH;
		 }
		 else {
			 return STD_LOW;
		 }
	 }

Std_ReturnType Spi_WriteIB (Spi_ChannelType Channel, Spi_DataBufferType* DataBufferPtr) {
	  switch(Channel) {
			case spi2: {
				config_GPIOB();
	       Dio_WriteChannel(DIO_CHANNEL_PB12,STD_LOW);//GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	     SPI_I2S_SendData(SPI2,*DataBufferPtr);
	  while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_BSY) == RESET) {
		  }
		    Dio_WriteChannel(DIO_CHANNEL_PB12,STD_HIGH); //GPIO_SetBits(GPIOB,GPIO_Pin_12);
			return E_OK;
	        }
			break;
        }
		return E_NOT_OK;
		}

Std_ReturnType Spi_ReadIB ( Spi_ChannelType Channel, Spi_DataBufferType* DataBufferPointer) {
	  switch (Channel) {
			case spi2: {
				config_GPIOB();
				DataBufferPointer = SPI_I2S_ReceiveData(SPI2);
				return E_OK;
				break;
			}
		}
		return E_NOT_OK;
	}

int main() {
			Spi_Init ();
	  while(1) {
			if(Spi_ReadIB(spi2,&data) == E_OK) {
				config_GPIOC();
				while(1) {
				Dio_WriteChannel(DIO_CHANNEL_PC13,STD_LOW);//GPIO_SetBits(GPIOC,GPIO_Pin_13);
				Delay_ms(200);
				Dio_WriteChannel(DIO_CHANNEL_PC13,STD_HIGH);//GPIO_ResetBits(GPIOC,GPIO_Pin_13);
				Delay_ms(200);
				}
		 }
	 }
	}

	