#ifndef GPS_H
#define GPS_H

# define  PI  3.141592653589793238462643


float GPS_getDistance (float currentLong, float currentlat, float destlong, float destlat);
float GPS_calcTotalDistance(float distance, float *totalDistance);

#endif
