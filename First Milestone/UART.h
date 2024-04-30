//UART 
#ifndef UART_H
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
void UART6_INIT(void);

char UART0_READ(void);
void UART0_WRITE(unsigned char tx_data);

unsigned char UART2_READ(void);
void UART2_WRITE(unsigned char data);

unsigned char UART6_READ(void);
void UART6_WRITE(unsigned char data);
#endif
