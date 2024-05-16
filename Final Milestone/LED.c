#include "tm4c123gh6pm.h"
#include "GPIO.h"
#include "LED.h"

void LED_Init(void)
{
	GPIO_InitPort(GPIO_PORTF);
	GPIO_SetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_OUTPUT);
	GPIO_SetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_OUTPUT);
	GPIO_SetPinDirection(GPIO_PORTF,GPIO_PIN3,GPIO_OUTPUT);
}
void LED_RedON(void)
{
	GPIO_SetPinValue(GPIO_PORTF,GPIO_PIN1,GPIO_HIGH);
}
void LED_BlueON(void)
 {
	GPIO_SetPinValue(GPIO_PORTF,GPIO_PIN2,GPIO_HIGH);
}
void LED_GreenON(void)
{
	GPIO_SetPinValue(GPIO_PORTF,GPIO_PIN3,GPIO_HIGH);
}

void LED_RedOFF(void)
{
	GPIO_SetPinValue(GPIO_PORTF,GPIO_PIN1,GPIO_LOW);
}
void LED_BlueOFF(void)
{
	GPIO_SetPinValue(GPIO_PORTF,GPIO_PIN2,GPIO_LOW);
}
void LED_GreenOFF(void)
{
	GPIO_SetPinValue(GPIO_PORTF,GPIO_PIN3,GPIO_LOW);
}
