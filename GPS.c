/**************************************************************************
*                                File GPS.c                               *
*                         Embedded project Team                           *
*                                                                         *
*           author/ Ahmed Karam  @ 24/4/24                                *
*                                                                         *
*                                                                         *
*                                                                         *
***************************************************************************/

# include "GPS.h"
# include "Bit_Utilies.h"

# include <math.h>

 const double EARTHRADIUS = 6371000;
	

float ToDegree (float angle) {
	int degree = (int)degree/100 ;
	float minutes = angle -(float)degree*100 ;
    return (degree+ (minutes/60) ) ;
	}

	// ToRad function to convert the angle from Todegree reading Torad
	
float ToRad(float angle) {
	  return angle*PI/180 ;
	}

	
	 //  Radian Angle
float GPS_getDistance (float currentLong, float currentlat, float destlong, float destlat) {

 float currentLongRad = ToRad(ToDegree(currentLong)); // longitude of current point
 float currentLatRad  = ToRad(ToDegree(currentlat )); // lattitude  of current point
 float destLongRad    = ToRad(ToDegree(destlong   )); // longitude of destination point
 float destLatRad     = ToRad(ToDegree(destlat    )); // lattitude of destination point

 // Get Difference
	float longDiff = destLongRad - currentLongRad;  // get the differance in longtitude
	float latDiff  = destLatRad  - currentLatRad ;  // get the differance in lattitude
	
 // Calculate Distance
 float  a = pow(sin(latDiff/2), 2)+ cos(currentLatRad) *cos(destLatRad) *pow(sin(longDiff/2),2);// Haversine formular 
 double c = 2*atan2(sqrt(a), sqrt(1-a));
    return  EARTHRADIUS * c ;
	
}













