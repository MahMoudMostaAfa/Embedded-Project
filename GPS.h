#ifndef GPS_H
#define GPS_H

# define  PI  3.141592653589793238462643


float GPS_main(int *pCurrIndex);
double GPS_getDistance (double currentLong, double currentlat, double destlong, double destlat);
void readGPS();
char* GPS_getOutput(int end);
double ToRad(double angle);
int GPS_Data(int currIndex);

#endif
