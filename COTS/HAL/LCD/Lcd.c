#include "../GPIO/GPIO.h"
void init_LCD(void){
/*in LCD Pin 4 >> Register Select command or data
  -------pin 5 >> Read/Write
  -------pin 6 >> Enable */
	
	GPIO_InitPort(GPIO_PORTA);
	GPIO_InitPort(GPIO_PORTB);
	// pin 4 >> pin 5 in port A ** pin 5 >> pin 6 ** in port A  pin 6 >> pin 7 in port A   
	GPIO_SetPinDirection(GPIO_PORTA,  GPIO_PIN5	 , GPIO_OUTPUT	);
	GPIO_SetPinDirection(GPIO_PORTA,  GPIO_PIN6	 , GPIO_OUTPUT	);
	GPIO_SetPinDirection(GPIO_PORTA,  GPIO_PIN7	 , GPIO_OUTPUT	);
 // port B from pin 0 to 7 output dat to lcd
	GPIO_SetPinDirection(GPIO_PORTB,  GPIO_PIN0	 , GPIO_OUTPUT	);
	GPIO_SetPinDirection(GPIO_PORTB,  GPIO_PIN1	 , GPIO_OUTPUT	);
	GPIO_SetPinDirection(GPIO_PORTB,  GPIO_PIN2	 , GPIO_OUTPUT	);	
	GPIO_SetPinDirection(GPIO_PORTB,  GPIO_PIN3	 , GPIO_OUTPUT	);
	GPIO_SetPinDirection(GPIO_PORTB,  GPIO_PIN4	 , GPIO_OUTPUT	);
	GPIO_SetPinDirection(GPIO_PORTB,  GPIO_PIN5	 , GPIO_OUTPUT	);	
	GPIO_SetPinDirection(GPIO_PORTB,  GPIO_PIN6	 , GPIO_OUTPUT	);
	GPIO_SetPinDirection(GPIO_PORTB,  GPIO_PIN6	 , GPIO_OUTPUT	);
	
}
void LCD_Send_command(char Command){
GPIO_PORTA_DATA_R &= ~0xE0;
GPIO_PORTB_DATA_R  = Command;
GPIO_PORTA_DATA_R = 0x80;
// delay function 
GPIO_PORTA_DATA_R &=~0x80	
}
void LCD_Send_Data(char Data){
GPIO_PORTA_DATA_R &= ~0xE0;
GPIO_PORTA_DATA_R |= 0x20;
GPIO_PORTB_DATA_R  = Data;
GPIO_PORTA_DATA_R = 0x80;
// delay function 
GPIO_PORTA_DATA_R &=~0x80	
}

