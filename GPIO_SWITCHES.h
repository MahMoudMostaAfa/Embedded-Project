
// Macros

#define RED_LED       0x02           
#define BLUE_LED      0x04           
#define GREEN_LED     0x08
#define ALL_LEDS      0x0E
#define ALL_SWITCHES  0x11


// Prototypes

void RGBLED_Init(void);
void SW_Init(void);
unsigned char switch1_in(void);     //input Switch 1 (pf0)
unsigned char switch2_in(void);     //if needed
void green_on(void);
void green_off(void);
void Distance_check(int pass_100_meter);
