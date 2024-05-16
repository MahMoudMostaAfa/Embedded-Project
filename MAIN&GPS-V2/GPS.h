#ifndef GPS_H
#define GPS_H
// Structure to store latitude and longitude
 typedef struct {
    double latitude;
    double longitude;
} Coordinates;


Coordinates parse_gps_data();
double calculate_distance(Coordinates start, Coordinates end);


#endif
