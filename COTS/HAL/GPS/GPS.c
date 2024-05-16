#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "tm4c123gh6pm.h"

#include "UART.h"
#include "GPIO.h"

#include "GPS.h"


void get_coordinates(uint8_t *coordinate, uint8_t* fix, uint32_t len){
uint8_t recieved_character;
    uint8_t i,k ;
    uint8_t GPS_Checkname[]="$GPRMC,";
    uint8_t m;
    m=0;
      for (i=0; i<len; i++) {
          if (coordinate[i] == GPS_Checkname[0] && coordinate[i+3] == GPS_Checkname[3]){
            fix[m]= coordinate[i];
            for(i; i<8; i++){
                fix[m]= coordinate[i];
                 m++;
                if (coordinate[i] == GPS_Checkname[6]){
                k=i;
                break;
                }
            }
          }   
      }
    strcpy (fix, "");    //Init GPS Array 
      m=0;
      k++;
      for (k; k<80; k++){
        recieved_character = coordinate[k];
        fix[m] = recieved_character;
        m++;
       if (recieved_character == '*') break;
      }
}


float atof2(uint8_t *str) {
    float result = 0.0;
    float fraction = 0.0;
    uint32_t divisor = 10;
    int32_t sign = 1;
    uint32_t decimal_seen = 0;

    // Handle leading whitespace
    while (*str == ' ') {
        str++;
    }

    // Handle optional sign
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // Process digits
    while (*str != '\0') {
        if (*str >= '0' && *str <= '9') {
            if (decimal_seen) {
                fraction += (*str - '0') / (float)divisor;
                divisor *= 10;
            } else {
                result = result * 10 + (*str - '0');
            }
        } else if (*str == '.') {
            decimal_seen = 1;
        } else {
            break; // Stop parsing on encountering non-numeric character
        }
        str++;
    }

    result += fraction;
    return result * sign;
}

float get_lat(uint8_t *fix, uint8_t len){
uint8_t i ;
uint8_t j=0;
uint8_t k=0;
static float lat_1;	
static uint8_t lat[10];
for(i=0; i<len; i++){
    if (fix[i] == comma){
    j++;
    }
    if(j == 1 && fix[i] == 'V'){
      break;  
     }
       if(j == 2 && fix[i]!= comma){
       lat[k]=fix[i];
       k++;
       }
       if(j == 3){
        lat[k]= '\0';
      if(fix[i] == 'S'){
        lat_1= -1 * atof2(lat);
        break;
      }
      else if(fix[i] == 'N'){
        lat_1= atof2(lat);
        break;
      }
    }
  }
     return lat_1;
}

float get_long(uint8_t *fix, uint8_t len){
uint8_t i=0;
uint8_t j=0;
uint8_t k=0;
static float lon_1 ;
static uint8_t lon[10];
for(i=0; i<len; i++){
    if (fix[i] == comma){
    j++;
    }
    if(j == 1 && fix[i] == 'V'){
      break;  
     }
       if(j == 4 && fix[i]!= comma){
       lon[k]=fix[i];
       k++;
       }
       if(j == 5){
        lon[k]= '\0';
      if(fix[i] == 'W'){
        lon_1= -1 * atof2(lon);
        break;
      }
      else if(fix[i] == 'E'){
        lon_1= atof2(lon);
        break;
      }
    }
  }
  return lon_1;
}

double ToDegree (double angle) {
int degree = (int) angle / 100 ;
float minutes = angle - (float) degree*100; 
return (degree+ (minutes/60));
}

float ToRadians(float degrees) {
    return degrees * (pi / 180.0);
}

float get_distance(float lat1, float lon1, float lat2, float lon2) {            //Printing integer or decimal?
    // Convert latitude and longitude from degrees to radians
    float dlat;
    float dlon;
	  float a;
	  float c;
	  float distance;
	  lat1 = ToRadians(ToDegree(lat1));
    lon1 = ToRadians(ToDegree(lon1));
    lat2 = ToRadians(ToDegree(lat2));
    lon2 = ToRadians(ToDegree(lon2));
    
    // Haversine formula
    dlat = lat2 - lat1;
    dlon = lon2 - lon1;
    a = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
    c = 2 * atan2(sqrt(a), sqrt(1 - a));
    distance = RADIUS_OF_EARTH * c;
    
    return (float) distance ;
}

void subs(float *lat1, float *lon1, float *lat2, float *lon2){
  *lat1= *lat2;
  *lon1= *lon2;
}

