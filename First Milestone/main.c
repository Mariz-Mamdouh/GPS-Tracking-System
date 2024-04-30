#include "GPIO.h"
#include "LED.h"
#include "UART.h"

uint32_t Button_1;

int main(){
	//Initialization of UART and GPIO Ports
	UART0_INIT();
	UART2_INIT();
	UART6_INIT();
	//Initialization of LED and Button
	LED_Init();
	GPIO_SetPinDirection(GPIO_PORTF, GPIO_PIN4, GPIO_INPUT);
	
