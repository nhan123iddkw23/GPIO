#include <stm32f10x.h>
#include <delay.h>
void config() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef LCD;
	LCD.GPIO_Mode = GPIO_Mode_Out_PP;
	LCD.GPIO_Pin = GPIO_Pin_All;
	LCD.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&LCD);
	}

void Lcd_Write_Command (char command) {
	   GPIOA->ODR = 0<<8;     //LCD_RS = 0;
     GPIOA->ODR = 0<<9;     //LCD_RW = 0;
     GPIOA->ODR = 1<<10;    //LCD_EN = 1;
     GPIOA->ODR = command;     //LCD_DATA = command;
     GPIOA->ODR = 0<<10;   // LCD_EN = 0;
     Delay_ms(10);	
}
void Lcd_Write_Data (char data)
{ 
     GPIOA->ODR = 1<<8;        //LCD_RS = 1;
     GPIOA->ODR = 0<<9;       //LCD_RW = 0;
     GPIOA->ODR = 1<<10;        //LCD_EN = 1;
     GPIOA->ODR = data;         // LCD_DATA = data;
     GPIOA->ODR = 0<<10;       // LCD_EN = 0;
     Delay_ms(10);              //Delay1KTCYx(10);
}
int main() {
	config();
	Lcd_Write_Command(0x03);
	Lcd_Write_Command(0x38);
	Lcd_Write_Command(0x06);
	Lcd_Write_Command(0x0c);
	Lcd_Write_Command(0x80);
	Lcd_Write_Data (0x41);
	Lcd_Write_Command(0x81);
	Lcd_Write_Data (0x42);
	}

	