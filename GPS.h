#ifndef GPS_H
#define GPS_H

# define  PI  3.141592653589793238462643


double GPS_getDistance (double currentLong, double currentlat, double destlong, double destlat);
double GPS_calcTotalDistance(double distance, double *totalDistance);

#endif
