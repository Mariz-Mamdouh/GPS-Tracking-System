#include"../UART_INIT/UART.c"
#include"string.h"
#include"stdint.h"
void UART_OutString(char *pt){
while(*pt){
UART0_WRITE(*pt);
pt++;
}
}

// *************** UART0 >> GPS functions***********
void GPS_Get_Data(char *GPS_Data,int len_GPS){
int i ;
	for(i=0;i < len_GPS;i++){
 	GPS_Data[i] = UART0_READ();
		UART0_WRITE(GPS_Data[i]);
	if(GPS_Data[i] == 'W')break;
// GPS_Data format $GPGGA,181908.00,3404.7041778,N,07044.3966270,
//W,4,13,1.00,495.144,M,29.200,M,0.10,0000*40
// we store until reach to W  such as $GPGGA,181908.00,3404.7041778,N,07044.3966270,W
}
	
}
// *************** UART2 >> LCD functions***********
// we need to set 8 pins as output and Calculate distance to see it on LCD

// *************** UART6 >> PC functions***********
int store_end_Point(){ //if PC send 'U' we need to store address in EEPPROM
	char UART6_Char = UART6_READ() ;
	if(UART6_Char == 'U'){
	return 1;
	}
	return 0;

} 
int main(){
	const int len_GPS = 100;
	char GPS_Data[len_GPS] = "0";
	UART0_INIT();
	UART6_INIT();
	while(1){
		GPS_Get_Data(GPS_Data,len_GPS); 
//store time and latitude and longitude we don't need time and we need to 
//separate between latitude and longitude	

	}
}