#include "tm4c123gh6pm.h"
#include "STD_TYPES.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
/*  
    RS=PD0
    RW=PD1
    EN=PD2

    D0 - PA7
    D1-  PA6
    D2 - PA5
    D3 - PB4
    D4 - PE5
    D5 - PE4
    D6 - PB1
    D7 - PB0
*/

 
void delay(long d)
{
   while(d--);
}
 
void Printdata(uint8_t data)
{ 
    // data = 8 bit hexadecimal data
  if ((data&0x01) ==0x01) 
	GPIO_PORTA_DATA_R |= 0x80;
  else                   
	GPIO_PORTA_DATA_R &= ~0x80;
  
  if ((data &0x02) ==0x02) 
	GPIO_PORTA_DATA_R |= 0x40;
  else                   
	GPIO_PORTA_DATA_R &= ~0x40;
  
  if ((data &0x04)==0x04) 
	GPIO_PORTA_DATA_R |= 0x20;
  else                   
	GPIO_PORTA_DATA_R &= ~0x20;
  
  if ((data &0x08) ==0x08) 
	GPIO_PORTB_DATA_R |= 0x10;
  else                   
	GPIO_PORTB_DATA_R &= ~0x10;
  
  if ((data &0x10) ==0x10) 	
	GPIO_PORTE_DATA_R |= 0x20;
  else                   
	GPIO_PORTE_DATA_R &= ~0x20;
  
  if ((data &0x20) ==0x20) 
	GPIO_PORTE_DATA_R |= 0x10;
  else                   
	GPIO_PORTE_DATA_R &= ~0x10;
  
  if ((data &0x40) ==0x40) 
	GPIO_PORTB_DATA_R |= 0x02;
  else                   
	GPIO_PORTB_DATA_R &= ~0x02;
  
  if ((data &0x80) ==0x80) 
	GPIO_PORTB_DATA_R |= 0x01;
  else                   
	GPIO_PORTB_DATA_R &= ~0x01;
}

void LCD_CMD(uint8_t cmd)
{
//		GPIO_PORTA_DATA_R &= 0x0;
//	GPIO_PORTB_DATA_R &= 0x0;
//	GPIO_PORTD_DATA_R &= 0x0;
//	GPIO_PORTE_DATA_R &= 0x0;
    Printdata(cmd);                  //pass the 8bit data in the datalines of lcd
    GPIO_PORTD_DATA_R &= ~ 0x02 ;    //turn off the R/W pin for write operation in lcd
    GPIO_PORTD_DATA_R &= ~ 0x01;     //turn off the RS for writing to the instruction register of lcd
    GPIO_PORTD_DATA_R |= 0x04;       //turn on the En of lcd for enabling the clock of lcd
    delay(10000);                    //wait for sometime
    GPIO_PORTD_DATA_R &=~ 0x04;      //Turn off the En of lcd  
}

void LCD_Init(void)
{
    //enable the clock of GPIO A,B,D,E
    SYSCTL_RCGCGPIO_R |= 0x1B;
    while((SYSCTL_PRGPIO_R & 0x0001)==0);
    //Digitalize these 8 pins
    GPIO_PORTA_DEN_R  |= 0xE0;
    GPIO_PORTB_DEN_R  |= 0x13;
    GPIO_PORTD_DEN_R  |= 0x07;
    GPIO_PORTE_DEN_R  |= 0x30;
    //config these 8 pins as output pins
    GPIO_PORTA_DIR_R  |= 0xE0;
    GPIO_PORTB_DIR_R  |= 0x13;
    GPIO_PORTD_DIR_R  |= 0x07;
    GPIO_PORTE_DIR_R  |= 0x30;
    LCD_CMD(0x38); //8bit mode utilising 16 columns and 2 rows
    LCD_CMD(0x06); // autoincrementing the cursor when prints the data in current  
    LCD_CMD(0x0C); //cursor off and display on
    LCD_CMD(0x01); //clearscreen
}


void LCD_SendChar(uint8_t data)
{
    Printdata(data);                  //pass the data in the datalines of lcd
    GPIO_PORTD_DATA_R &= ~ 0x02 ;    //turn off the R/W pin for write operation in lcd
    GPIO_PORTD_DATA_R |= 0x01;      //turn on the RS for writing to the data register of lcd
    GPIO_PORTD_DATA_R |= 0x04;     //turn on the En of lcd for enabling the clock of lcd
    delay(10000);                            //wait for sometime
    GPIO_PORTD_DATA_R &=~ 0x04;             //Turn off the En of lcd  
}

void LCD_SendString(uint8_t *str ,uint8_t len)
{
	uint8_t i;
   for (i=0;i<len;i++){
    LCD_SendChar(str[i]);
	 }
}

uint8_t strlength( uint8_t *str)
{
   uint8_t length = 0;
    uint8_t i;
    // Loop until the null terminator is encountered
    while (str[i] != '\0') {
        length++;
        i++;
    }
    
    return length;
}


//void reverse(uint8_t *str, uint8_t length){
    //uint8_t start = 0;
    //uint8_t end = length - 1;
    //while (start < end) {
       // uint8_t temp = str[start];
        //str[start] = str[end];
        //str[end] = temp;
        //start++;
        //end--;
  //  }
//}

// convert from integer to string
void itoa(int32_t num, uint8_t *str, uint8_t base)
  {
    uint8_t i = 0;
    uint8_t isNegative = 0;

    // Handle 0 explicitly, otherwise empty string is printed
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
    }

    // Handle negative numbers
    if (num < 0 && base == 10) {
        isNegative = 1;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num /= base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Null terminate string

    // Reverse the string
   // reverse(str, i);

}

void floatToString(double num, uint8_t *buffer, uint8_t precision)
  {
    uint8_t integerLength;
		uint8_t i;
    uint32_t digit;
		uint32_t integerPart = (uint32_t)num;
    double fractionalPart = num - integerPart;

    // Convert integer part to string
    itoa(integerPart, buffer, 10);

    // Find the position to start writing the fractional part
    integerLength = strlength(buffer);

    buffer[integerLength++] = '.';

    // Calculate the fractional part
    for (i = 0; i < precision; i++) {
        fractionalPart *= 10;
        digit = (int32_t)fractionalPart;
        buffer[integerLength++] = '0' + digit;
        fractionalPart -= digit;
    }

    // Null-terminate the string
    buffer[integerLength] = '\0';
}

