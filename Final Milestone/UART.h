#ifndef UART_H
#define UART_H

#include <stdint.h>

#define U          0x55               //Ascii code for U
#define CHECKSUM   0x2A               //Ascii code for *
#define ENTER      0x0D              //ASCII code for ENTER

#define UART_H
#define UART0_enable       0x0001
#define GPIOA_enable       0x0001
#define UART2_enable       0x0004
#define UART6_enable       0x0040
#define GPIOD_enable       0x0008
#define RXFE               0x00000010
#define TXFF               0x00000020
#define word_len           0x60    //8-bits
#define FEN                0x10  //set bit 5 
#define TXE                0x0100
#define RXE                0x0200
// define UART functions 
void UART0_INIT(void);
void UART2_INIT(void);

typedef enum {
    UART0 =0,
    UART2 =2,
}UART_NO;


void UART_Init(uint8_t UART_no);
uint8_t UART_Read_Char(uint8_t UART_no);
void UART_Write_Char(uint8_t UART_no,uint8_t data);
void UART_Get_String(uint8_t *Command, uint32_t len) ;
void UART_Get_coord(uint8_t *coordinate, uint32_t len);
void UART_Print_String(uint8_t UART_no ,uint8_t *pt);





#endif
