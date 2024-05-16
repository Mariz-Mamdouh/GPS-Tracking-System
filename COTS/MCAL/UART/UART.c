#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include <string.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "UART.h"

#include "GPIO.h"

void UART0_INIT(void)
{
    SYSCTL_RCGCUART_R  |= UART0_enable;
    SYSCTL_RCGCGPIO_R  |= GPIOA_enable;
    while((SYSCTL_PRGPIO_R & GPIOA_enable)==0);
    UART0_CTL_R        &=~UART_CTL_UARTEN;
    UART0_IBRD_R        = 104;
    UART0_FBRD_R        = 11;
    UART0_LCRH_R        = word_len | FEN;
    UART0_CTL_R         = TXE | RXE | UART_CTL_UARTEN;
    GPIO_InitPort(GPIO_PORTA);
    GPIO_PORTA_AFSEL_R |= 0X0003;
    GPIO_PORTA_PCTL_R   = 0X0011;
}

/*--------------------------------uart2---------------------------------*/
void UART2_INIT(void){
    // For GPS
	SYSCTL_RCGCUART_R |=0x04; //1)UART2 =2^5   0010 0000
	SYSCTL_RCGCGPIO_R |= 0x08; //2) GpioD= 2^4  0001 0000
	while((SYSCTL_PRGPIO_R&0x08)==0); // delay
	GPIO_PORTD_LOCK_R =GPIO_LOCK_KEY; // unlocking the PORTS
	GPIO_PORTD_AFSEL_R |=0xC0; //3) AFSEL PD6, PD7  0000 1100 0000
	GPIO_PORTD_PCTL_R |= 0x11000000; //4) PCTL to PD6, PD7
     //
	UART2_CTL_R&=~(0x01);  // 1.1) Disable UARTEN
	UART2_IBRD_R=104;      // (80MHz/16*9600)=520 ,,,,, 104 ==>> 16MHZ
	UART2_FBRD_R=11;
	UART2_LCRH_R=0x070; // 1.4)8bit,no parity bits, one stop,FIFOs 0000 0111 0000
	UART2_CTL_R|=0x301; //1.5) enabling the UART, TX, RX
	GPIO_PORTD_DEN_R|=0xC0; // PD6, PD7 Digital enable
	GPIO_PORTD_AMSEL_R&= ~(0xC0); // turn off analog function PORTD  ,,,,,,, AMSEL?======>?PE4,PE5
}






void UART_Init(uint8_t UART_no) { 
	switch (UART_no)
	{
	case UART0:
		SYSCTL_RCGCUART_R |= 0x01;  // activate UART0
		SYSCTL_RCGCGPIO_R |= 0x01; //activate GPIOA
        while ((SYSCTL_PRGPIO_R & 0x01) == 0){};	
		
		
		UART0_CTL_R &= ~0x0001;       // disable UART
		UART0_IBRD_R = 104;           // IBRD=int (80000000/(16*9600))=int (520.8333) 
		UART0_FBRD_R = 11;            // FBRD int (0.8333 * 64 + 0.5)
		UART0_LCRH_R = 0x0070;        // 8-bit word length, enable FIFO 001110000 
		UART0_CTL_R = 0x0301;         // enable RXE, TXE and UART 001100000001 
		GPIO_PORTA_AFSEL_R |= 0x03;   // enable alt function PAO,PA1 
		GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00)+0x00000011;
		/*
		configure
		UART for PAO, PA1
		*/
		GPIO_PORTA_DEN_R |= 0x03;     // enable digital I/O on PAO, PA1 
		GPIO_PORTA_AMSEL_R &= ~0x03;  // disable analog function on PAO, PA1
		break;

	case UART2:
		SYSCTL_RCGCUART_R |= 0x04; 
		SYSCTL_RCGCGPIO_R |= 0x08;
    	while ((SYSCTL_PRGPIO_R & 0x08) == 0); 
		while ((SYSCTL_PRUART_R & 0x04) == 0); 
		GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;
		GPIO_PORTD_CR_R |= 0xC0;
	
		UART2_CTL_R &= ~0X01;       // disable UART
		UART2_IBRD_R = 104;           // IBRD=int (80000000/(16*9600))=int (520.8333) 
		UART2_FBRD_R = 11;            // FBRD int (0.8333 * 64 + 0.5)
		UART2_LCRH_R = 0x0070;        // 8-bit word length, enable FIFO 001110000 
		UART2_CTL_R = 0x0301;         // enable RXE, TXE and UART 001100000001 
		GPIO_PORTD_AFSEL_R |= 0xC0;   // enable alt function PD6,PD7
		GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0x00FFFFFF) + 0x11000000;
		GPIO_PORTD_DIR_R |= 0xC0;
		GPIO_PORTD_DEN_R |= 0xC0;     // enable digital I/O on PD6, PD7 
		GPIO_PORTD_AMSEL_R &= ~0xC0;  // disable analog function on PD6, PD7
		break;
	default:
		break;
	}				// should be called only once

}
//to read UART data
uint8_t UART_Read_Char(uint8_t UART_no){
	switch (UART_no)
	{
	case UART0:
		while((UART0_FR_R & 0X0010) !=0);
		return (uint8_t)(UART0_DR_R & 0XFF);
		break;
	case UART2 :
		while((UART2_FR_R & 0X0010) !=0);
		return (uint8_t)(UART2_DR_R & 0XFF);
		break;
	default:
		break;
	}

}
//to write UART data
void UART_Write_Char(uint8_t UART_no,uint8_t data){
	switch (UART_no)
	{
	case UART0:
		while((UART0_FR_R & 0X0020) !=0); 
		UART0_DR_R=data;
		break;
	case UART2 :
		while((UART2_FR_R & 0X0020) !=0); 
		UART2_DR_R=data;
		break;
	default:
		break;
	}

}

void UART_Get_String(uint8_t *Command, uint32_t len){
	uint8_t character;
	uint8_t i;
	for(i=0; i<len; i++){
		character= UART_Read_Char(UART0);
		if(character != ENTER){
				Command[i]=character;
    	        UART_Write_Char(UART0,character);
		}
		else if(character == ENTER ) {
			break;	
		}		
	}
}

void UART_Get_coord(uint8_t *coordinate, uint32_t len){

	 	uint8_t recievedchar;
		uint8_t i;
		uint8_t m;
    uint8_t k;
    uint8_t g;
	  uint8_t l;
		uint8_t GPS_Checkname[]= "$GPRMC,"; 
	   k=0;

		for(i=0; i<800; i++){
			coordinate[k] = UART_Read_Char(UART2);
			if (coordinate[0]==GPS_Checkname[0]){
                i++;
                for(m =1 ; m<=6 ; m++){
                    coordinate[m]=UART_Read_Char(UART2);
                }
                
                if (strcmp(coordinate,GPS_Checkname)==0){
                    break; 
                    
                    }
                    
                else {
                    k=0;
                }       
			}
			else if(coordinate[0]!=GPS_Checkname[0])
			{
				strcpy (coordinate, "");
				k=0;
			}
			
		}
		strcpy (coordinate, "");
        for(g=0; g<len; g++){
			coordinate[g]=UART_Read_Char(UART2);
			if(coordinate[g]==CHECKSUM){
				break;
			}
		 }
				
		 
			
}

void UART_Print_String(uint8_t UART_no, uint8_t *pt){
	while(*pt){
		switch (UART_no){
			case UART0 :																					// to terminate at null character
				UART_Write_Char(UART0, *pt);            // print character by character
				pt++;                           // get next character by incresing the pointer pointing to the string

			case UART2 :
				UART_Write_Char(UART0, *pt);            // print character by character
				pt++; 
		}
	}
}

