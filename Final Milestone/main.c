#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#include "tm4c123gh6pm.h"

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "GPIO.h"
#include "UART.h"
#include "STK.h"

#include "LCD.h"
#include "GPS.h"
#include "LED.h"
#include "EEPROM.h"

//		int main(){
//			// variable declaration:
//			 uint8_t command_U[2];
//			 uint8_t dest_lat[10];
//			 uint8_t dest_long[10];
//			 float dest_latitude;
//       float dest_longitude;
//			char gpsData[100]; 
//			char current_long[10]; 
//			char current_lat[10];
//			 // LATITUDE & LONGITUDE used to store trajectory point;
//       float LATITUDE[50]={0}; //check if not predefining the array size is correct
//       float LONGITUDE[50]={0};
//			 uint8_t coordinate[80]= {0}, lat_string[15], lon_string[15];
//  uint8_t flag;
//  uint8_t l=0;
//  uint8_t comma_counter=0;
//			// init:
//		SysTick_Init();
//		LED_Init();
//		GPIO_InitPort(GPIO_PORTF);
//		GPIO_InitPort(GPIO_PORTA);
//    UART0_INIT();
//    UART2_INIT();
//		 		//LED_RedON();
//		UART_Print_String(UART0,"ENTER U or N \n");
//		UART_Get_String(command_U, 2);
//if(command_U[0] == 'U'){		
//  while(1){
//		LED_GreenON();
//		// EEPROM CODE:		
//	}
//		}
//else{ 
//		UART_Print_String(UART0, "ENTER THE DESTINATION LATITUDE \n");
//	 UART_Get_String(dest_lat,10);
//   UART_Print_String(UART0, "ENTER THE DESTINATION LONGITUDE \n");
//	 UART_Get_String(dest_long,10);	
//	 // RED ON 
//	 LED_RedON();
//	 dest_latitude = atof2(dest_lat);
//   dest_longitude = atof2(dest_long); 
//	while(1){
//	memset(coordinate,0,80);
//	UART_Get_coord(coordinate, 80);
//			do{
//    if(coordinate[l] == comma){
//      comma_counter++;
//    }
//    else if(coordinate[l] == 'A' && comma_counter==1 ){
//      flag=1;
//    }
//    else if(coordinate[l] != 'A' && comma_counter==1){
//      UART_Get_coord(coordinate, 80);
//      l=0;
//    }
//		l++;    
//  }while(flag==0);
//	UART_Print_String(UART0,coordinate);
//	}

//}
// 
//		}

int main(){
  uint8_t coordinate[80]= {0}, lat_string[15], lon_string[15];
	int address = 0, lat_eeprom, lon_eeprom;
  uint8_t dest_lat[10];
  uint8_t dest_long[10];
  uint8_t command_U[2];
  uint8_t DIST[6];
  float LATITUDE[]={0}; //check if not predefining the array size is correct
  float LONGITUDE[]={0};
  uint8_t LCD_Print[]={0};
  uint8_t flag;
  uint8_t l=0;
  uint8_t comma_counter=0;
  static float lat1 ;
  static float lon1;
  static float lat2 ;
  static float lon2;
  static float dest_latitude;
  static float dest_longitude;
	uint8_t lat2_print[10],lon2_print[10];

  uint32_t Switch_1;
  uint8_t  latcounter=0;
  uint8_t  longcounter=0;
  float distance=0;
	float delta_distance = 0;
  uint32_t coordinateLength;
  uint32_t LCDLength;
  float CHECK_DISTANCE = 100;
  const uint32_t length_Of_Coordinate = 400 ;

  
		LED_Init();
		SysTick_Init();
		EEPROMINIT();
		GPIO_InitPort(GPIO_PORTF);
		GPIO_InitPort(GPIO_PORTA);
    UART0_INIT();
    UART2_INIT();
		UART_Print_String(UART0,"ENTER U or N \n");
		UART_Get_String(command_U, 2);
		if(strcmp(command_U, "U") ==0){
		
    while(1){
		  lat_eeprom = EEPROM_Read(address);
			address += 4;
			lat_eeprom = lat_eeprom / 100000;
			lon_eeprom = EEPROM_Read(address);
			lon_eeprom = lon_eeprom / 100000;
			address += 4;
			sprintf(lat_string, "%f", lat_eeprom);
			sprintf(lon_string, "%f", lon_eeprom);
			UART_Print_String(UART0, lat_string);
			UART_Print_String(UART0, ",");
			UART_Print_String(UART0, lon_string);
		}

  }
    UART_Print_String(UART0, "ENTER THE DESTINATION LATITUDE \n");
    UART_Get_String(dest_lat,10);
    UART_Print_String(UART0, "ENTER THE DESTINATION LONGITUDE \n");
    UART_Get_String(dest_long,10);
		LED_RedON();
		dest_latitude = atof2(dest_lat);
		dest_longitude = atof2(dest_long); 
		memset(coordinate,0,80);
		UART_Get_coord(coordinate, 80);
  
  
		do{
    if(coordinate[l] == comma){
      comma_counter++;
    }
    else if(coordinate[l] == 'A' && comma_counter==1 ){
      flag=1;
    }
    else if(coordinate[l] != 'A' && comma_counter==1){
      UART_Get_coord(coordinate, 80);
      l=0;
    }
		l++;    
  }while(flag==0);
  
  
  
  UART_Print_String(UART0, coordinate);
  
//  LED_GreenON();
//  SysTick_Wait10ms(50);
//  LED_GreenOFF();
  coordinateLength = strlen(coordinate);
  lat1=get_lat(coordinate,coordinateLength);  
  lon1=get_long(coordinate,coordinateLength);
  LATITUDE[0] =lat1;
  LONGITUDE[0]=lat2;
  latcounter=1;
  longcounter=1;  
  LCD_Init();
  delay(10000);  
  LCD_CMD(0x80); //cursor to first row and first column
  
  
while(1){
  
    SysTick_Wait10ms(50);
    memset(coordinate,0,80);
    UART_Get_coord(coordinate, 80);
  
    do{
    if(coordinate[l] == comma){
      comma_counter++;
    }
    else if(coordinate[l] == 'A' && comma_counter==1 ){
      flag=1;
    }
    else if(coordinate[l] != 'A' && comma_counter==1){
      UART_Get_coord(coordinate, 80);
      l=0;
    }
   l++;    
  }while(flag==0);
    
  

  //UART_Print_String(UART0, coordinate);
  lat2=get_lat(coordinate,coordinateLength);
  lon2=get_long(coordinate,coordinateLength);
	 sprintf(lat2_print, "%f", lat2);
   UART_Print_String(UART0, lat2_print);
	 sprintf(lon2_print, "%f", lon2);
   UART_Print_String(UART0, lon2_print);

  LATITUDE[latcounter++]=lat2;;
  LONGITUDE[longcounter++]=lon2;

  delta_distance = get_distance(lat1,lon1,lat2,lon2);
	if(delta_distance < 0){
	delta_distance  = -delta_distance;
	}
	if(delta_distance <= 2 & delta_distance >=0.5){
	distance += delta_distance;
  subs(&lat1, &lon1, &lat2, &lon2);
	CHECK_DISTANCE = get_distance(lat1,lon1,dest_latitude,dest_longitude);
	}

  sprintf(DIST, "%f", distance);
  LCD_CMD(0x80);
  LCD_SendString("DISTANCE: ", 10);
  LCDLength = strlen(DIST);
  LCD_CMD(0xC0);
  LCD_SendString(DIST, LCDLength);
  if (CHECK_DISTANCE<8){
   LED_GreenON();
 
      /*floatToString(distance, DIST, 2);
      //LCD_Print = "DISTANCE : "  ;
      LCDLength = strlen(DIST);
      LCD_String(DIST, LCDLength);*/
    }
	lat_eeprom = lat1 * 100000;
	lon_eeprom = lon1 * 100000;
		
//	EEPROM_Write(address, lat_eeprom);
//	address += 4;
//	EEPROM_Write(address, lon_eeprom);
//	address += 4;
//		
    SysTick_Wait10ms(20);
  }

}
