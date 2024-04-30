#include "tm4c123gh6pm.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "../../GPIO/GPIO.c"
#include "UART.h"
//*--------------------------------uart0---------------------------------*/
void UART0_INIT(void)
{
    SYSCTL_RCGCUART_R  |= UART0_enable;
    SYSCTL_RCGCGPIO_R  |= GPIOA_enable;	
    while((SYSCTL_PRGPIO_R & GPIOA_enable)==0);
    UART0_CTL_R        &=~UART_CTL_UARTEN;                   
    UART0_IBRD_R        = 520;
    UART0_FBRD_R        = 53;		
    UART0_LCRH_R        = word_len | FEN;
    UART0_CTL_R         = TXE | RXE | UART_CTL_UARTEN;	
    GPIO_InitPort(GPIO_PORTA);
    GPIO_PORTA_AFSEL_R |= 0X0003;
    GPIO_PORTA_PCTL_R   = 0X0011;
}
//*--------------------------------uart2---------------------------------*/
void UART2_INIT(void)
{
SYSCTL_RCGCUART_R  |= UART2_enable;
SYSCTL_RCGCGPIO_R |= GPIOD_enable;
while((SYSCTL_PRGPIO_R & GPIOD_enable)==0);
while((SYSCTL_RCGCUART_R & UART2_enable)==0)
GPIO_InitPort(GPIO_PORTD);
GPIO_PORTD_AFSEL_R |= 0X00F0;
GPIO_PORTD_PCTL_R  |= 0x11110000;
UART2_CTL_R        &=~UART_CTL_UARTEN;
UART2_IBRD_R        = 520;
UART2_FBRD_R        = 53;
UART2_LCRH_R	    = word_len | FEN;
UART2_CTL_R        &=~UART_CTL_UARTEN;	
}

//*--------------------------------uart6---------------------------------*/
void UART6_INIT(void)
{
    SYSCTL_RCGCUART_R  |= UART6_enable;
    SYSCTL_RCGCGPIO_R  |= GPIOD_enable;
    while((SYSCTL_PRGPIO_R & GPIOD_enable)==0);
     GPIO_InitPort(GPIO_PORTD);
    GPIO_PORTD_AFSEL_R |=0X00F0;
    GPIO_PORTD_PCTL_R  |=0X11110000;
    UART6_CTL_R        &=~UART_CTL_UARTEN;
    UART6_IBRD_R        = 520;
    UART6_FBRD_R        = 53;
    UART6_LCRH_R	      = word_len | FEN;
    UART0_CTL_R         = TXE | RXE | UART_CTL_UARTEN;	
}

//*----------------------------------rx_u0-------------------------------*/
 char UART0_READ(void)
 {
    // check if RXF empty 
    while ( (UART0_FR_R & RXFE) != 0 );	
    return (char)(UART0_DR_R & 0x000000FF);	
}

//*----------------------------------tx_u0-------------------------------*/
void UART0_WRITE(unsigned char tx_data)
{
    // check if there is space in tx_fifo
      while ( (UART0_FR_R & TXFF) != 0 );
      UART0_DR_R = tx_data ; 	
}
//*----------------------------------rx_u2-------------------------------*/
unsigned char UART2_READ(void){
// check if data arrived 
while ( (UART2_FR_R & 0x00000010) != 0 );	
return (unsigned char )(UART2_DR_R & 0x00000FF);	

}
//*----------------------------------tx_u2-------------------------------*/
void UART2_WRITE(unsigned char data){
// check if there is space in tx_fifo
while ( (UART2_FR_R & 0x00000020) != 0 );
UART2_DR_R = data ; 	
}

//*----------------------------------rx_u6-------------------------------*/
unsigned char UART6_READ(void)
{
    // check if data arrived 
    while ( (UART6_FR_R & 0x00000010) != 0 );	
    return (unsigned char )(UART6_DR_R & 0x00000FF);	
}

//*----------------------------------tx_u6-------------------------------*/
void UART6_WRITE(unsigned char data)
{
    // check if there is space in tx_fifo
    while ( (UART6_FR_R & 0x00000020) != 0 );
    UART6_DR_R = data ; 	
}

