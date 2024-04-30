#include "tm4c123gh6pm.h"
#include "MASKS.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
//*--------------------------------uart0---------------------------------*/
void UART0_INIT(void){
SYSCTL_RCGCUART_R  |= UART0_enable;
SYSCTL_RCGCGPIO_R  |= GPIOA_enable;	
while((SYSCTL_PRGPIO_R & GPIOA_enable)==0);
UART0_CTL_R        &=~UART_CTL_UARTEN;                   
UART0_IBRD_R        = 104;
UART0_FBRD_R        = 11;		
UART0_LCRH_R        = word_len | FEN;
UART0_CTL_R         = TXE | RXE | UART_CTL_UARTEN;	
GPIO_PORTA_AFSEL_R |= 0X0003;
GPIO_PORTA_PCTL_R   = 0X0011;
GPIO_PORTA_DEN_R   |= 0x0003;
GPIO_PORTA_DIR_R   |= 0x0001;
GPIO_PORTA_AMSEL_R &= 0X03;
}
//*--------------------------------uart6---------------------------------*/
void UART6_INIT(void){
SYSCTL_RCGCUART_R  |= UART6_enable;
SYSCTL_RCGCGPIO_R  |= GPIOD_enable;
while((SYSCTL_PRGPIO_R & GPIOD_enable)==0);
GPIO_PORTD_AFSEL_R |=0X0030;
GPIO_PORTD_PCTL_R  |=0X00110000;
GPIO_PORTD_DEN_R   |=0X0030;
GPIO_PORTD_DIR_R   |=0X0020;
UART6_CTL_R        &=~UART_CTL_UARTEN;
UART6_IBRD_R        = 104;
UART6_FBRD_R        = 11;
UART6_LCRH_R	      = word_len | FEN;
UART0_CTL_R         = TXE | RXE | UART_CTL_UARTEN;	
}
//*----------------------------------rx_u0-------------------------------*/
 char UART0_READ(void){
// check if RXF empty 
  while ( (UART0_FR_R & RXFE) != 0 );	
  return (char)(UART0_DR_R & 0x000000FF);	
}
//*----------------------------------tx_u0-------------------------------*/
void UART0_WRITE(unsigned char tx_data){
// check if there is space in tx_fifo
  while ( (UART0_FR_R & TXFF) != 0 );
  UART0_DR_R = tx_data ; 	
}
//*----------------------------------rx_u6-------------------------------*/
unsigned char UART6_READ(void){
// check if data arrived 
while ( (UART6_FR_R & 0x00000010) == 1 );	
return (unsigned char )(UART6_DR_R & 0x00000FF);	
}
//*----------------------------------tx_u6-------------------------------*/
void UART6_WRITE(unsigned char data){
// check if there is space in tx_fifo
while ( (UART6_FR_R & 0x00000020) == 1 );
UART6_DR_R = data ; 	
}



