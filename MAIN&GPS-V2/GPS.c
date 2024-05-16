#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "GPS.h"
#include "UART.h"




char logName[] = "$GPRMC,"; //Logname to get the required Log
char finalLog[100];	//Taking the overall GPS log as 1D array
char GPS_Array[12][18]; //Formatting the GPS log into 2D array to analyze its data

char *container ; //pointer used in formatting the GPS log data
// Function to parse GPS data and extract latitude and longitude

Coordinates parse_gps_data() {
	char charRead;
	while(1) {
		char i = 0;
		//Loop to get the required logname
		for(; i < 7; i++) {
			charRead = UART_5_Read();
			if(charRead != logName[i]) {
				//break if its not the logname
				break;
			}
		}
		//If the for loop finished without breaking then its the required logname
		if(i == 7) {//	i == 7 if the loop didn't break
			charRead = UART_5_Read();//	update charRead
			break;
		}
	}

	strcpy(finalLog, ""); //Clear finalLog

	//loop to get log after "$GPRMC,"  (not taking logName)
	char logIndex = 0;
	while(charRead != '*') {
		finalLog[logIndex++] = charRead;
		charRead = UART_5_Read();
	}
    //now the finalLog array contains the GPS log line without the log header
     Coordinates coords;

       int counter = 0 ;
    container = strtok(finalLog , ",") ; // strtok return pointer to first element of array

   while (container != NULL){  //Arranging the 2D array to take the GPS log data
     strcpy (GPS_Array[counter++] , container ) ;
     container = strtok(NULL , ",") ;
   }

   if (strcmp(GPS_Array[1] , "A") == 0 )   //verifying that the collected data is valid & we use strcmp as we are dealing with strings in the 2D array
    {
         //collecting data from the GPS log

        if (strcmp(GPS_Array[3] , "N") == 0)
            coords.latitude = atof (GPS_Array[2]) ;       //latitude value if N save it as a +ve in lattitude and vice versa
        else
            coords.latitude = -atof (GPS_Array[2]) ;


        if (strcmp(GPS_Array[5] , "E") == 0)
            coords.longitude = atof (GPS_Array[4]) ;       //longitude value if E save it as a +ve in longPoints and vice versa
        else
            coords.longitude = -atof (GPS_Array[4]) ;

        return coords;
   }
   else{
         coords.latitude = -1;
         coords.longitude = -1;
         return coords;
    
   };

}


float ToRad(float angle) {
	int degree = (int)angle/100 ;
	float minutes = angle -(float)degree*100 ;
    angle = (degree+ (minutes/60) ) ;
    return angle*PI/180 ;
	}

// Function to calculate distance between two coordinates (in meters)
double calculate_distance(Coordinates start, Coordinates end) {
    const double R = 6371000; // Radius of the Earth in meters
  
 float currentLongRad = ToRad(start.longitude); // longitude of current point
 float currentLatRad  = ToRad(start.latitude); // lattitude  of current point
 float destLongRad    = ToRad(end.longitude); // longitude of destination point
 float destLatRad     = ToRad(end.latitude); // lattitude of destination point

 // Get Difference
	float longDiff = destLongRad - currentLongRad;  // get the differance in longtitude
	float latDiff  = destLatRad  - currentLatRad ;  // get the differance in lattitude

 // Calculate Distance
 float  a = pow(sin(latDiff/2), 2)+ cos(currentLatRad) *cos(destLatRad) *pow(sin(longDiff/2),2);// Haversine formula
 float c = 2*atan2(sqrt(a), sqrt(1-a));
    return  R * c ;
   


}
