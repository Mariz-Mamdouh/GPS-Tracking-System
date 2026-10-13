#ifndef GPS_H
#define GPS_H

#include <stdint.h>

#define RADIUS_OF_EARTH 6371*1000       // Earth's radius
#define pi 3.1414592
#define CHECKSUM 0x2A
#define comma   0x2C


void get_coordinates(uint8_t *coordinate, uint8_t* fix , uint32_t len); // coordinate from gps , extract fix
double ToDegree (double angle);
float ToRadians(float degrees) ;
float get_distance(float lat1, float lon1, float lat2, float lon2);
void subs(float *lat1, float *lon1, float *lat2, float *lon2);
float atof2(uint8_t *str);
float get_lat(uint8_t *fix, uint8_t len );
float get_long(uint8_t *fix, uint8_t len);







#endif
