/**< LIB */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "tm4c123gh6pm.h"
/**< MCAL */
#include "GPIO.h"


Std_ReturnType GPIO_InitPort(uint8_t PortID)
{
    Std_ReturnType Local_FunctionStatus = E_NOT_OK;
    if(PortID>=GPIO_PORTA && PortID<=GPIO_PORTF)
	{
		SET_BIT(SYSCTL_RCGCGPIO_R,PortID); 						                // To enable a clock and active PORT A
		while(GET_BIT(SYSCTL_PRGPIO_R,PortID) == 0); 			                // Wait till the Clock be stable
		switch(PortID)
		{
			case GPIO_PORTA:
				GPIO_PORTA_LOCK_R  = GPIO_LOCK_KEY; 							// Unlocks the GPIOCR register so we can allow the commit
				GPIO_PORTA_CR_R    = GPIO_ENABLE_7_BIT;						    // Allow changes to PA7-0 
				GPIO_PORTA_AFSEL_R = 0x00;										// Disable analog functions
				GPIO_PORTA_PCTL_R  = GPIO_PCTL_VALUE; 					    	// GPIO_PCTL_VALUE-->To make all the pins in PORT A work as GPIO 
				GPIO_PORTA_DEN_R   = 0xFF;										// to enable the pin PA0-PA7 as digital 
                Local_FunctionStatus = E_OK;
			break;
			case GPIO_PORTB:
				GPIO_PORTB_LOCK_R  = GPIO_LOCK_KEY; 							// Unlocks the GPIOCR register so we can allow the commit
				GPIO_PORTB_CR_R    = GPIO_ENABLE_7_BIT;					    	// Allow changes to PB7-0 
				GPIO_PORTB_AFSEL_R = 0x00;										// Disable the alternative functions
				GPIO_PORTB_PCTL_R  = GPIO_PCTL_VALUE; 						    // GPIO_PCTL_VALUE-->To make all the pins in PORT B work as GPIO 
				GPIO_PORTB_DEN_R   = 0xFF;										// to enable the pin PB0-PB7 as digital 
                Local_FunctionStatus = E_OK;
			break;
			case GPIO_PORTC:
				GPIO_PORTC_LOCK_R  = GPIO_LOCK_KEY; 							// Unlocks the GPIOCR register so we can allow the commit
				GPIO_PORTC_CR_R    = GPIO_ENABLE_7_BIT;						    // Allow changes to PC7-0 
				GPIO_PORTC_AFSEL_R = 0x00;										// Disable the alternative functions
				GPIO_PORTC_PCTL_R  = GPIO_PCTL_VALUE; 						    // GPIO_PCTL_VALUE-->To make all the pins in PORT C work as GPIO  
				GPIO_PORTC_DEN_R   = 0xFF;										// to enable the pin PC0-PC7 as digital 
                Local_FunctionStatus = E_OK;
			break;
			case GPIO_PORTD:
				GPIO_PORTD_LOCK_R  = GPIO_LOCK_KEY; 							// Unlocks the GPIOCR register so we can allow the commit
				GPIO_PORTD_CR_R    = GPIO_ENABLE_7_BIT;						    // Allow changes to PD7-0 
				GPIO_PORTD_AFSEL_R = 0x00;										// Disable the alternative functions
				GPIO_PORTD_PCTL_R  = GPIO_PCTL_VALUE; 						    // GPIO_PCTL_VALUE-->To make all the pins in PORT D work as GPIO
				GPIO_PORTD_DEN_R   = 0xFF;										// to enable the pin PD0-PD7 as digital 
                Local_FunctionStatus = E_OK;
			break;
			case GPIO_PORTE:
				GPIO_PORTE_LOCK_R  = GPIO_LOCK_KEY; 							// Unlocks the GPIOCR register so we can allow the commit
				GPIO_PORTE_CR_R    = GPIO_ENABLE_7_BIT;						    // Allow changes to PE7-0 
				GPIO_PORTE_AFSEL_R = 0x00;										// Disable the alternative functions
				GPIO_PORTE_PCTL_R  = GPIO_PCTL_VALUE; 						    // GPIO_PCTL_VALUE-->To make all the pins in PORT E work as GPIO 
				GPIO_PORTE_DEN_R   = 0xFF;										// to enable the pin PE0-PE7 as digital 
                Local_FunctionStatus = E_OK;
			break;
			case GPIO_PORTF:
				GPIO_PORTF_LOCK_R  = GPIO_LOCK_KEY; 							// Unlocks the GPIOCR register so we can allow the commit
				GPIO_PORTF_CR_R    = GPIO_ENABLE_7_BIT;					    	// Allow changes to PF7-0 
				GPIO_PORTF_AFSEL_R = 0x00;										// Disable the alternative functions
				GPIO_PORTF_PCTL_R  = GPIO_PCTL_VALUE; 					    	// GPIO_PCTL_VALUE-->To make all the pins in PORT F work as GPIO 
				GPIO_PORTF_DEN_R   = 0xFF;										// to enable the pin PF0-PF7 as digital 
                Local_FunctionStatus = E_OK;
			break;
			default:
                Local_FunctionStatus = E_NOT_OK; 
            break;
		}
	}
	else
	{
		Local_FunctionStatus = E_NOT_OK;
	}

    return Local_FunctionStatus;
}

Std_ReturnType GPIO_SetPinDirection(uint8_t PortID, uint8_t PinId , uint8_t PinDirection)
{
    Std_ReturnType Local_FunctionStatus = E_NOT_OK;

    if((PortID<=GPIO_PORTF && PortID>=GPIO_PORTA) && (PinId<=GPIO_PIN7 && PinId>=GPIO_PIN0) && (PinDirection==GPIO_INPUT || PinDirection==GPIO_OUTPUT))
	{
		switch(PortID)
		{
			case GPIO_PORTA:
				switch(PinDirection)
				{
					case GPIO_OUTPUT:
						SET_BIT(GPIO_PORTA_DIR_R,PinId);		// Set the direction of pin to be output
					break;
					case GPIO_INPUT:
						CLR_BIT(GPIO_PORTA_DIR_R,PinId);		// Set the direction of pin to be input
					break;
				}
                Local_FunctionStatus = E_OK;
			break;
			case GPIO_PORTB:
				switch(PinDirection)
				{
					case GPIO_OUTPUT:
						SET_BIT(GPIO_PORTB_DIR_R,PinId);		// Set the direction of pin to be output
					break;
					case GPIO_INPUT:
						CLR_BIT(GPIO_PORTB_DIR_R,PinId);		// Set the direction of pin to be input
					break;
				}
                Local_FunctionStatus = E_OK;
			break;
			case GPIO_PORTC:
				switch(PinDirection)
				{
					case GPIO_OUTPUT:
						SET_BIT(GPIO_PORTC_DIR_R,PinId);		// Set the direction of pin to be output
					break;
					case GPIO_INPUT:
						CLR_BIT(GPIO_PORTC_DIR_R,PinId);		// Set the direction of pin to be input
					break;
				}
                Local_FunctionStatus = E_OK;
			break;
			case GPIO_PORTD:	
				switch(PinDirection)
				{
					case GPIO_OUTPUT:
						SET_BIT(GPIO_PORTD_DIR_R,PinId);		// Set the direction of pin to be output
					break;
					case GPIO_INPUT:
						CLR_BIT(GPIO_PORTD_DIR_R,PinId);		// Set the direction of pin to be input
					break;
				}
                Local_FunctionStatus = E_OK;
			break;
			case GPIO_PORTE:
			    if(PinId<=GPIO_PIN4)
			    {
			        switch(PinDirection)
                    {
                        case GPIO_OUTPUT:
                            SET_BIT(GPIO_PORTE_DIR_R,PinId);     // Set the direction of pin to be output
                        break;
                        case GPIO_INPUT:
                            CLR_BIT(GPIO_PORTE_DIR_R,PinId);     // Set the direction of pin to be input
                        break;
                    }
                    Local_FunctionStatus = E_OK;
			    }
			    else
			    {
			        Local_FunctionStatus = E_NOT_OK;
			    }
			break;
			case GPIO_PORTF:
			    if(PinId<=GPIO_PIN4)
			    {
			        switch(PinDirection)
                    {
                        case GPIO_OUTPUT:
                            SET_BIT(GPIO_PORTF_DIR_R,PinId);     // Set the direction of pin to be output
                        break;
                        case GPIO_INPUT:
                            CLR_BIT(GPIO_PORTF_DIR_R,PinId);     // Set the direction of pin to be input
                        break;
                    }
                    Local_FunctionStatus = E_OK;
			    }
			    else
			    {
			        Local_FunctionStatus = E_NOT_OK;
			    }
			break;
			default:
                Local_FunctionStatus = E_NOT_OK; 
            break;
		}
	}
	else
	{
		Local_FunctionStatus = E_NOT_OK;
	}

    return Local_FunctionStatus;   
}

Std_ReturnType GPIO_SetPinValue(uint8_t PortID, uint8_t PinId , uint8_t PinValue)
{
    Std_ReturnType Local_FunctionStatus=E_NOT_OK;
    if((PortID<=GPIO_PORTF && PortID>=GPIO_PORTA) && (PinId<=GPIO_PIN7 && PinId>=GPIO_PIN0) && (PinValue==GPIO_HIGH || PinValue==GPIO_LOW))
	{
		switch(PortID)
		{
			case GPIO_PORTA:
				switch(PinValue)
				{
					case GPIO_HIGH:
						SET_BIT(GPIO_PORTA_DATA_R,PinId);		
					case GPIO_LOW:
						CLR_BIT(GPIO_PORTA_DATA_R,PinId);		
					break;
				}
                Local_FunctionStatus = E_OK;
			break;
			case GPIO_PORTB:
				switch(PinValue)
				{
					case GPIO_HIGH:
						SET_BIT(GPIO_PORTB_DATA_R,PinId);		
					break;
					case GPIO_LOW:
						CLR_BIT(GPIO_PORTB_DATA_R,PinId);		
					break;
				}
                Local_FunctionStatus = E_OK;
			break;
			case GPIO_PORTC:
				switch(PinValue)
				{
					case GPIO_HIGH:
						SET_BIT(GPIO_PORTC_DATA_R,PinId);		
					break;
					case GPIO_LOW:
						CLR_BIT(GPIO_PORTC_DATA_R,PinId);		
					break;
				}
                Local_FunctionStatus = E_OK;
			break;
			case GPIO_PORTD:	
				switch(PinValue)
				{
					case GPIO_HIGH:
						SET_BIT(GPIO_PORTD_DATA_R,PinId);		
					break;
					case GPIO_LOW:
						CLR_BIT(GPIO_PORTD_DATA_R,PinId);		
					break;
				}
                Local_FunctionStatus = E_OK;
			break;
			case GPIO_PORTE:
			    if(PinId<=GPIO_PIN4)
			    {
			        switch(PinValue)
                    {
                        case GPIO_HIGH:
                            SET_BIT(GPIO_PORTE_DATA_R,PinId);     
                        break;
                        case GPIO_LOW:
                            CLR_BIT(GPIO_PORTE_DATA_R,PinId);     
                        break;
                    }
                    Local_FunctionStatus = E_OK;
			    }
			    else
			    {
			        Local_FunctionStatus = E_NOT_OK;
			    }
			break;
			case GPIO_PORTF:
			    if(PinId<=GPIO_PIN4)
			    {
			        switch(PinValue)
                    {
                        case GPIO_HIGH:
                            SET_BIT(GPIO_PORTF_DATA_R,PinId);     
                        break;
                        case GPIO_LOW:
                            CLR_BIT(GPIO_PORTF_DATA_R,PinId);     
                        break;
                    }
                    Local_FunctionStatus = E_OK;
			    }
			    else
			    {
			        Local_FunctionStatus = E_NOT_OK;
			    }
			break;
			default:
                Local_FunctionStatus = E_NOT_OK; 
            break;
		}
	}
	else
	{
		Local_FunctionStatus = E_NOT_OK;
	}

    return Local_FunctionStatus; 
}

Std_ReturnType GPIO_GetPinValue(uint8_t PortID, uint8_t PinId , uint32_t *ReturnedPinValue)
{
    Std_ReturnType Local_FunctionStatus = E_NOT_OK;
    	if((ReturnedPinValue != NULL) && (PortID<=GPIO_PORTF && PortID>=GPIO_PORTA) && (PinId>=GPIO_PIN0 && PinId<=GPIO_PIN7))
	{
		switch(PortID)
		{
			case GPIO_PORTA:
                *ReturnedPinValue = GET_BIT(GPIO_PORTA_DATA_R,PinId);
                Local_FunctionStatus = E_OK;
			break;
			case GPIO_PORTB:
                *ReturnedPinValue = GET_BIT(GPIO_PORTB_DATA_R,PinId);
                Local_FunctionStatus = E_OK;
			break;
			case GPIO_PORTC:
                *ReturnedPinValue = GET_BIT(GPIO_PORTC_DATA_R,PinId);
                Local_FunctionStatus = E_OK;
			break;
			case GPIO_PORTD:
                *ReturnedPinValue = GET_BIT(GPIO_PORTD_DATA_R,PinId);
                Local_FunctionStatus = E_OK;
			break;
			case GPIO_PORTE:
                *ReturnedPinValue = GET_BIT(GPIO_PORTE_DATA_R,PinId);
                Local_FunctionStatus = E_OK;
			break;
			case GPIO_PORTF:
                *ReturnedPinValue = GET_BIT(GPIO_PORTF_DATA_R,PinId);
                Local_FunctionStatus = E_OK;
			break;
		}
	}
	else
	{
		Local_FunctionStatus = E_NOT_OK;
	}

    return Local_FunctionStatus; 
}

Std_ReturnType GPIO_SetPortDirection(uint8_t PortID, uint8_t PortDirection)
{
    Std_ReturnType Local_FunctionStatus = E_NOT_OK;

    if((PortID>=GPIO_PORTA && PortID<=GPIO_PORTF) && (PortDirection==GPIO_OUTPUT || PortDirection==GPIO_INPUT))
	{
		switch(PortID)
		{
			case GPIO_PORTA:
				switch(PortDirection)
				{
					case GPIO_OUTPUT: 
                        GPIO_PORTA_DIR_R = 0XFF;
                        Local_FunctionStatus = E_OK;
                    break;
					case GPIO_INPUT:
                        GPIO_PORTA_DIR_R = 0X00;
                        Local_FunctionStatus = E_OK;
                    break;
					default:
                        Local_FunctionStatus = E_NOT_OK;
                    break;
				}
			break;
			case GPIO_PORTB:
				switch(PortDirection)
				{
					case GPIO_OUTPUT:
                        GPIO_PORTB_DIR_R = 0XFF;
                        Local_FunctionStatus = E_OK;
                    break;
					case GPIO_INPUT:
                        GPIO_PORTB_DIR_R = 0X00;
                        Local_FunctionStatus = E_OK;
                    break;
					default:
                        Local_FunctionStatus = E_NOT_OK;
                    break;
				}
			break;	
			case GPIO_PORTC:
				switch(PortDirection)
				{
					case GPIO_OUTPUT:
                        GPIO_PORTC_DIR_R = 0XFF;
                        Local_FunctionStatus = E_OK;
                    break;
					case GPIO_INPUT:
                        GPIO_PORTC_DIR_R = 0X00;
                        Local_FunctionStatus = E_OK;
                    break;
					default:
                        Local_FunctionStatus = E_NOT_OK;
                    break;
				}
			break;	
			case GPIO_PORTD:
				switch(PortDirection)
				{
					case GPIO_OUTPUT:
                        GPIO_PORTD_DIR_R = 0XFF;
                        Local_FunctionStatus = E_OK;
                    break;
					case GPIO_INPUT:
                        GPIO_PORTD_DIR_R = 0X00;
                        Local_FunctionStatus = E_OK;
                    break;
					default:
                        Local_FunctionStatus = E_NOT_OK;
                    break;
				}
			break;	
			case GPIO_PORTE:
				switch(PortDirection)
				{
					case GPIO_OUTPUT:
                        GPIO_PORTE_DIR_R = 0XFF;
                        Local_FunctionStatus = E_OK;
                    break;
					case GPIO_INPUT:
                        GPIO_PORTE_DIR_R = 0X00;
                        Local_FunctionStatus = E_OK;
                    break;
					default:
                        Local_FunctionStatus = E_NOT_OK;
                    break;
				}
			break;	
			case GPIO_PORTF:
				switch(PortDirection)
				{
					case GPIO_OUTPUT:
                        GPIO_PORTF_DIR_R = 0XFF;
                        Local_FunctionStatus = E_OK;
                    break;
					case GPIO_INPUT:
                        GPIO_PORTF_DIR_R = 0X00;
                        Local_FunctionStatus = E_OK;
                    break;
					default:
                        Local_FunctionStatus = E_NOT_OK;
                    break;
				}
			break;				
		}
	}
	else
	{
		Local_FunctionStatus = E_NOT_OK;
	}

    return Local_FunctionStatus; 
}

Std_ReturnType GPIO_SetPortValue(uint8_t PortID, uint8_t PortValue)
{
    Std_ReturnType Local_FunctionStatus = E_NOT_OK;

    if((PortID>=GPIO_PORTA && PortID<=GPIO_PORTF) && (PortValue==GPIO_LOW || PortValue==GPIO_HIGH))
	{
		switch(PortID)
		{
			case GPIO_PORTA:
                GPIO_PORTA_DATA_R = PortValue;
                Local_FunctionStatus = E_OK;
            break;
			case GPIO_PORTB:
                GPIO_PORTB_DATA_R = PortValue;
                Local_FunctionStatus = E_OK;
            break;
			case GPIO_PORTC:
                GPIO_PORTC_DATA_R = PortValue;
                Local_FunctionStatus = E_OK;
            break;
			case GPIO_PORTD:
                GPIO_PORTD_DATA_R = PortValue;
                Local_FunctionStatus = E_OK;
            break;
			case GPIO_PORTE:
                GPIO_PORTE_DATA_R = PortValue;
                Local_FunctionStatus = E_OK;
            break;
			case GPIO_PORTF:
                GPIO_PORTF_DATA_R = PortValue;
                Local_FunctionStatus = E_OK;
            break;
			default:
            Local_FunctionStatus = E_NOT_OK;
            break;
		}
	}
	else
	{
		Local_FunctionStatus = E_NOT_OK;
	}

    return Local_FunctionStatus; 
}

Std_ReturnType GPIO_GetPortValue(uint8_t PortID, uint32_t *ReturnedPortValue)
{
    Std_ReturnType Local_FunctionStatus = E_NOT_OK;

    if((PortID>=GPIO_PORTA && PortID<=GPIO_PORTF) && (ReturnedPortValue != NULL))
	{
		switch(PortID)
		{
			case GPIO_PORTA:
                *ReturnedPortValue = GPIO_PORTA_DATA_R;
                Local_FunctionStatus = E_OK;
            break;
			case GPIO_PORTB:
                *ReturnedPortValue = GPIO_PORTB_DATA_R;
                Local_FunctionStatus = E_OK;
            break;
			case GPIO_PORTC:
                *ReturnedPortValue = GPIO_PORTC_DATA_R;
                Local_FunctionStatus = E_OK;
            break;
			case GPIO_PORTD:
                *ReturnedPortValue = GPIO_PORTD_DATA_R;
                Local_FunctionStatus = E_OK;
            break;
			case GPIO_PORTE:
                *ReturnedPortValue = GPIO_PORTE_DATA_R;
                Local_FunctionStatus = E_OK;
            break;
			case GPIO_PORTF:
                *ReturnedPortValue = GPIO_PORTF_DATA_R;
                Local_FunctionStatus = E_OK;
            break;
			default:
            Local_FunctionStatus = E_NOT_OK;
            break;
		}
	}
	else
	{
		Local_FunctionStatus = E_NOT_OK;
	}

    return Local_FunctionStatus; 
}

Std_ReturnType GPIO_TogglePinValue(uint8_t PortID, uint8_t PinId)
{
    Std_ReturnType Local_FunctionStatus = E_NOT_OK;

     if((PortID<=GPIO_PORTF && PortID>=GPIO_PORTA) && (PinId<=GPIO_PIN7 && PinId>=GPIO_PIN0))
    {
        switch(PortID)
        {
        case GPIO_PORTA:
            TOG_BIT(GPIO_PORTA_DATA_R,PinId);
            break;
        case GPIO_PORTB:
            TOG_BIT(GPIO_PORTB_DATA_R,PinId);
            break;
        case GPIO_PORTC:
            TOG_BIT(GPIO_PORTC_DATA_R,PinId);
            break;
        case GPIO_PORTD:
            TOG_BIT(GPIO_PORTD_DATA_R,PinId);
            break;
        case GPIO_PORTE:
            if(PinId<=GPIO_PIN4)
            {
                TOG_BIT(GPIO_PORTE_DATA_R,PinId);
            }
            else
            {
                Local_FunctionStatus = E_NOT_OK;
            }
            break;
        case GPIO_PORTF:
            if(PinId<=GPIO_PIN4)
            {
                TOG_BIT(GPIO_PORTF_DATA_R,PinId);
            }
            else
            {
                Local_FunctionStatus = E_NOT_OK;
            }
            break;
        default:
            Local_FunctionStatus = E_NOT_OK;
        break;
        }
    }
    else
    {
        Local_FunctionStatus = E_NOT_OK;
    }

    return Local_FunctionStatus; 
}
