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
# include "bit_utilies.h"
#include "UART.h"
#include "UART.c"
# include <math.h>
#include <string.h>
#include <stdlib.h>

const double EARTHRADIUS = 6371000;

char logName[] = "$GPRMC,"; //Logname to get the required Log
char finalLog[100];	//Taking the overall GPS log as 1D array
char GPS_Array[12][18]; //Formatting the GPS log into 2D array to analyze its data
char *container ; //pointer used in formatting the GPS log data

float clong , clat , deviceSpeed ;
int date ;
const float destLong , destLat ;


void readGPS() {
	char charRead;
	while(1) {
		char i = 0;
		//Loop to get the required logname
		for(; i < 7; i++) {
			charRead = UART_0_Read();
			if(charRead != logName[i]) {
				//break if its not the logname
				break;
			}
		}
		//If the for loop finished without breaking then its the required logname
		if(i == 7) {//	i == 7 if the loop didn't break
			charRead = UART_0_Read();//	update charRead
			break;
		}
	}

	strcpy(finalLog, ""); //Clear finalLog

	//loop to get log after "$GPRMC,"  (not taking logName)
	char logIndex = 0;
	while(charRead != '*') {
		finalLog[logIndex++] = charRead;
		charRead = UART_0_Read();
	}
    //now the finalLog array contains the GPS log line without the log header

}

void GPS_Data(){

   char counter = 0 ;
   container = strtok(finalLog , ",") ;

   while (container != NULL){  //Arranging the 2D array to take the GPS log data
     strcpy (GPS_Array[counter++] , container ) ;
     container = strtok(NULL , ",") ;
   }

   while (strcmp(GPS_Array[1] , "A") == 0 )   //verifying that the collected data is valid & we use strcmp as we are dealing with strings in the 2D array
    {
         //collecting data from the GPS log

        if (strcmp(GPS_Array[3] , "N") == 0)
            clat = atof (GPS_Array[2]) ;       //latitude value
        else
            clat = -atof (GPS_Array[2]) ;


        if (strcmp(GPS_Array[5] , "E") == 0)
            clong = atof (GPS_Array[4]) ;       //longitude value
        else
            clong = -atof (GPS_Array[4]) ;


        deviceSpeed = atof (GPS_Array[6]);       //speed value
        date = atoi (GPS_Array[8]);
   }



}




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
 float  a = pow(sin(latDiff/2), 2)+ cos(currentLatRad) *cos(destLatRad) *pow(sin(longDiff/2),2);// Haversine formula
 double c = 2*atan2(sqrt(a), sqrt(1-a));
    return  EARTHRADIUS * c ;

}

// Calculate the total Distance
// inputs:
// distance : distance moved between two points
// totalDistance : pointer to the total distance variable
float GPS_calcTotalDistance(float distance, float *totalDistance) {
    *totalDistance += distance;
    return *totalDistance;
}


















