#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "tm4c123gh6pm.h"
#include "STK.h"

#include <stdint.h>

void SysTick_Init(void){
    NVIC_ST_CTRL_R = 0; // 1) disable SysTick during setup 
    NVIC_ST_RELOAD_R = 0x00FFFFFF; // 2) maximum reload value 
    NVIC_ST_CURRENT_R = 0; // 3) any write to CURRENT clears it 
    NVIC_ST_CTRL_R = 0x00000005; // 4) enable SysTick with core clock
}

 // The delay parameter is in units of the 80 MHz core clock(12.5 ns)

void SysTick_Wait(uint32_t delay){
    NVIC_ST_RELOAD_R = delay-1; 
    NVIC_ST_CURRENT_R = 0;
     // number of counts
     // any value written to CURRENT clears
     while((NVIC_ST_CTRL_R & 0x00010000)==0) ; // wait for flag
     
}
 // Call this routine to wait for delay*10ms 
void SysTick_Wait10ms(uint32_t delay){ 
    uint8_t i;
    for(i=0; i<delay; i++){ 
        SysTick_Wait(160000); // wait 10ms
    }
}