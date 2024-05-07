#include "GPS.h"
#include "bit_utilies.h"
#include "UART.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

const double EARTHRADIUS = 6371000;

char logName[] = "$GPRMC,"; //Logname to get the required Log
char finalLog[100];	//Taking the overall GPS log as 1D array
char GPS_Array[12][18]; //Formatting the GPS log into 2D array to analyze its data
char *container ; //pointer used in formatting the GPS log data

double clong , clat , deviceSpeed ;
int date ;
const double destLong , destLat ;


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
   container = strtok(finalLog , ",") ; // strtok return pointer to first element of array

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



	// ToRad function to convert the angle from Todegree reading Torad

double ToRad(double angle) {
	int degree = (int)angle/100 ;
	double minutes = angle -(double)degree*100 ;
    angle = (degree+ (minutes/60) ) ;
    return angle*PI/180 ;
	}


	 //  Radian Angle
double GPS_getDistance (double currentLong, double currentlat, double destlong, double destlat) {

 double currentLongRad = ToRad(currentLong); // longitude of current point
 double currentLatRad  = ToRad(currentlat); // lattitude  of current point
 double destLongRad    = ToRad(destlong); // longitude of destination point
 double destLatRad     = ToRad(destlat); // lattitude of destination point

 // Get Difference
	double longDiff = destLongRad - currentLongRad;  // get the differance in longtitude
	double latDiff  = destLatRad  - currentLatRad ;  // get the differance in lattitude

 // Calculate Distance
 double  a = pow(sin(latDiff/2), 2)+ cos(currentLatRad) *cos(destLatRad) *pow(sin(longDiff/2),2);// Haversine formula
 double c = 2*atan2(sqrt(a), sqrt(1-a));
    return  EARTHRADIUS * c ;

}

// Calculate the total Distance
// inputs:
// distance : distance moved between two points
// totalDistance : pointer to the total distance variable
double GPS_calcTotalDistance(double distance, double *totalDistance) {
    *totalDistance += distance;
    return *totalDistance;
}


















