#ifndef GPIO_H
#define GPIO_H

#include "STD_TYPES.h"

#define GPIO_PORTA			0
#define GPIO_PORTB			1
#define GPIO_PORTC			2
#define GPIO_PORTD			3
#define GPIO_PORTE			4
#define GPIO_PORTF			5

#define GPIO_PIN0 			0
#define GPIO_PIN1			1
#define GPIO_PIN2			2
#define GPIO_PIN3			3
#define GPIO_PIN4			4
#define GPIO_PIN5			5
#define GPIO_PIN6			6
#define GPIO_PIN7			7

#define GPIO_OUTPUT			1
#define GPIO_INPUT			0

#define GPIO_LOW            0   
#define GPIO_HIGH           1   

#define GPIO_SW1            0x01

#define GPIO_LOCK_KEY				0x4C4F434B
#define GPIO_ENABLE_7_BIT			0x000000FF	
#define GPIO_PCTL_VALUE				0x00000000

Std_ReturnType GPIO_InitPort(uint8_t PortID);

Std_ReturnType GPIO_SetPinDirection(uint8_t PortID, uint8_t PinId , uint8_t PinDirection);

Std_ReturnType GPIO_SetPinValue(uint8_t PortID, uint8_t PinId , uint8_t PinValue);

Std_ReturnType GPIO_GetPinValue(uint8_t PortID, uint8_t PinId , uint32_t *ReturnedPinValue);

Std_ReturnType GPIO_SetPortDirection(uint8_t PortID, uint8_t PortDirection);

Std_ReturnType GPIO_SetPortValue(uint8_t PortID, uint8_t PortValue);

Std_ReturnType GPIO_GetPortValue(uint8_t PortID, uint32_t *ReturnedPortValue);

Std_ReturnType GPIO_TogglePinValue(uint8_t PortID, uint8_t PinId);


#endif /* GPIO_H */
