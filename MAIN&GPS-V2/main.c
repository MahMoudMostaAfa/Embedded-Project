#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include"tm4c123gh6pm.h"
#include"LCD.h"
#include "SysTick_Timer.h"
#include "UART.h"
#include "GPS.h"
#include "GPIO_SWITCHES.h"
 #define MAX_POINTS 80 // Maximum number of points to store
volatile bool collect_points = true;

void send_points_to_eeprom(Coordinates *points, int point_count) {
     char gpsOutput[1000];
     char *ptr = gpsOutput;
     int i;

    for (i = 0; i < point_count; i++) {
        // Use snprintf to ensure no buffer overflow
        ptr += snprintf(ptr, sizeof(gpsOutput) - (ptr - gpsOutput), "%f,%f|", points[i].latitude, points[i].longitude);
    }

    // Calculate the length of the initialized data in gpsOutput
    int length = ptr - gpsOutput;

    // Write only the initialized data to EEPROM
    EEPROM_writeall(gpsOutput, length);
}

void float_to_string(float value, char *str) {
    sprintf(str, "%.2lf", value); // Assuming distance is printed with 2 decimal places
}

// Function to display distance on LCD
void display_distance_on_lcd(float distance) {
    char distance_str[16]; // Assuming maximum distance string length is 16
    float_to_string(distance, distance_str);
    LCD_WriteString("Distance: ");
    LCD_WriteString(distance_str);
    LCD_WriteString(" meters");
}


int main() {
    Coordinates start_coords, current_coords;
    Coordinates points[MAX_POINTS]; // Array to store latitude and longitude point // Initialize LCD
    LCD4bits_Init();
    RGBLED_Init();
    SW_Init();
    enable_SW_Interrupts();
    SysTick_Init();
    UART_0_Init();
    UART_5_Init();
    int point_count = 0;
    float total_distance = 0;

    // Main loop
    while (1) {

      //  if(switch1_in()==1){
       //  collect_points = false;
       // }
        if(total_distance>100){
            green_on();
        }
        if(collect_points){
   // Parse GPS data and extract latitude and longitude
        current_coords = parse_gps_data();

        // If start coordinates are not set, set them
        if (start_coords.latitude == 0 && start_coords.longitude == 0) {
            start_coords = current_coords;
        } else {
            // check if gps data invalid
            if(start_coords.latitude == -1 && start_coords.longitude == -1) continue
            // Calculate distance moved from start coordinates
            float distance = calculate_distance(start_coords, current_coords);
            total_distance += distance;

            // If distance moved is more than 2 meters, save the current coordinates
            if (distance > 2 && point_count < MAX_POINTS) {
                points[point_count++] = current_coords;
                // Reset start coordinates
                start_coords = current_coords;
            }
        }

        // Print total distance moved
       
        // Display distance on LCD
         display_distance_on_lcd(total_distance);
        wait_ms(2000); // Delay for 2 second 
        LCD4bits_Cmd(0x01); // Clear display screen

        }else{
             // Stop collecting points and send collected points to EEPROM
            send_points_to_eeprom(points, point_count);
            green_off();
            red_on();
            wait_ms(2000); // Delay for 2 second 
            break; // Exit the main loop
        }
     
    }

    return 0;
}
