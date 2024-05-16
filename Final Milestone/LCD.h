#ifndef LCD_H
#define LCD_H
#include "STD_TYPES.h"
#include <stdint.h>

void LCD_Init(void);
void LCD_CMD(uint8_t cmd);
void Printdata(uint8_t data);
void LCD_SendChar(uint8_t data);
void LCD_SendString(uint8_t *str ,uint8_t len);
void delay(long d);
void floatToString(double num, uint8_t *buffer, uint8_t precision);
void itoa(int32_t num, uint8_t *str, uint8_t base);
Std_ReturnType convert_uint32_to_string(float value, uint8_t *str);
#endif
