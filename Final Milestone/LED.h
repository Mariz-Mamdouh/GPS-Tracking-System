#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include <string.h>
#include "math.h"
#define leds            0x0E

void LED_Init(void);

void LED_RedON(void);
void LED_GreenON(void);
void LED_BlueON(void);

void LED_RedOFF(void);
void LED_GreenOFF(void);
void LED_BlueOFF(void);

