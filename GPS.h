#ifndef GPS_H
#define GPS_H

# define  PI  3.141592653589793238462643


float GPS_main(int *pCurrIndex);
float GPS_getDistance (float currentLong, float currentlat, float destlong, float destlat);
void readGPS();
char* GPS_getOutput(int end);
float ToRad(float angle);
int GPS_Data(int currIndex);

#endif
