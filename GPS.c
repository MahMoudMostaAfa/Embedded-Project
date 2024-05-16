#include "GPS.h"
#include "bit_utilies.h"
#include "UART.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const float EARTHRADIUS = 6371000;

char logName[] = "$GPRMC,"; //Logname to get the required Log
char finalLog[100];	//Taking the overall GPS log as 1D array
char GPS_Array[12][18]; //Formatting the GPS log into 2D array to analyze its data
char *container ; //pointer used in formatting the GPS log data



float longPoints[200];
float latPoints[200];

char gpsOutput[1000];

float GPS_main(int *pCurrIndex){
	float small_dist;

    int currIndex = *pCurrIndex;
    int status=0;
    readGPS();    // the finalLog array is ready
    status = GPS_Data(currIndex);  // longitude points[] and latitude points[] arrays are ready
                          //
    if (status==-1){
        return -1;
    }

    if (currIndex ==0){

        *pCurrIndex +=1;
        return 0 ;
    }

  small_dist = GPS_getDistance(longPoints[currIndex-1] , latPoints[currIndex-1] , longPoints[currIndex] , latPoints[currIndex]); // getting the distance walked between 2 points
                                                                                                                                          //
    if (small_dist < 1.0){
        return 0;
    }

    *pCurrIndex +=1;

    return small_dist ;
}

char* GPS_getOutput(int end){
    char *ptr=gpsOutput;
    int i=0;
    for (i=0 ; i<end ; i++){
        sprintf(ptr , "%f,%f|" , longPoints[i] , latPoints[i]) ;
        ptr = strchr(ptr, '|')+1;

    }

    return gpsOutput ;
}

void readGPS() {
	char charRead;
	char logIndex;
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
	 logIndex = 0;
	while(charRead != '*') {
		finalLog[logIndex++] = charRead;
		charRead = UART_5_Read();
	}
    //now the finalLog array contains the GPS log line without the log header

}

int GPS_Data(int currIndex){


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
            latPoints[currIndex] = atof (GPS_Array[2]) ;       //latitude value if N save it as a +ve in lattitude and vice versa
        else
            latPoints[currIndex] = -atof (GPS_Array[2]) ;


        if (strcmp(GPS_Array[5] , "E") == 0)
            longPoints[currIndex] = atof (GPS_Array[4]) ;       //longitude value if E save it as a +ve in longPoints and vice versa
        else
            longPoints[currIndex] = -atof (GPS_Array[4]) ;

        return 0;
   }
   else return -1;
}

	// ToRad function to convert the angle from Todegree reading Torad

float ToRad(float angle) {
	int degree = (int)angle/100 ;
	float minutes = angle -(float)degree*100 ;
    angle = (degree+ (minutes/60) ) ;
    return angle*PI/180 ;
	}


	 //  Radian Angle
float GPS_getDistance (float currentLong, float currentlat, float destlong, float destlat) {

 float currentLongRad = ToRad(currentLong); // longitude of current point
 float currentLatRad  = ToRad(currentlat); // lattitude  of current point
 float destLongRad    = ToRad(destlong); // longitude of destination point
 float destLatRad     = ToRad(destlat); // lattitude of destination point

 // Get Difference
	float longDiff = destLongRad - currentLongRad;  // get the differance in longtitude
	float latDiff  = destLatRad  - currentLatRad ;  // get the differance in lattitude

 // Calculate Distance
 float  a = pow(sin(latDiff/2), 2)+ cos(currentLatRad) *cos(destLatRad) *pow(sin(longDiff/2),2);// Haversine formula
 float c = 2*atan2(sqrt(a), sqrt(1-a));
    return  EARTHRADIUS * c ;

}

