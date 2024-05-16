#ifndef EEPROM_H
#define EEPROM_H

#include "STD_TYPES.h"

void EEPROMINIT(void);

void EEPROM_Write(uint32_t address, uint32_t data);

uint32_t EEPROM_Read(uint32_t address);


#endif