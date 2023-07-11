#include <stm32f10x.h>
#include <delay.h>

#define LCD_RS GPIO_Pin_3
#define LCD_RW GPIO_Pin_4
#define LCD_E  GPIO_Pin_5

void config() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef PortA;
	PortA.GPIO_Mode = GPIO_Mode_Out_PP;
	PortA.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	PortA.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&PortA);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef PortB;
	PortB.GPIO_Mode = GPIO_Mode_Out_PP;
	PortB.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	PortB.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&PortB);
}

 void Lcd_Write_Command (char command) {
	 GPIO_ResetBits(GPIOB,LCD_RW);
	 GPIO_ResetBits(GPIOB,LCD_RS);
	 GPIO_ResetBits(GPIOB,LCD_E);
	 GPIO_Write(GPIOA,command);
	 GPIO_SetBits(GPIOB,LCD_E);
	 Delay_ms(2);
 }
 
 void Lcd_Write_Data(char data) {
	  GPIO_ResetBits(GPIOB,LCD_RW);
	  GPIO_SetBits(GPIOB,LCD_RS);
	  GPIO_ResetBits(GPIOB,LCD_E);
	  GPIO_Write(GPIOA,data);
	  GPIO_SetBits(GPIOB,LCD_E);
	  Delay_ms(2);
 }
 
int main() {
	 config();
	 Lcd_Write_Command(0x01); // xoa man hinh 
	 Lcd_Write_Command(0x03); // dua man hinh ve che do bat dau
	 Lcd_Write_Command(0x38);  // che do 8 bit
	 Lcd_Write_Command(0x06);  //tu dong dua con tro den vi tri ke tiep
	 Lcd_Write_Command(0x0c); // bat tat hien thi con tro
	 Lcd_Write_Command(0x80); // dau dong thu nhat
	 Lcd_Write_Data(0x42);
	 while(1);
 }
 