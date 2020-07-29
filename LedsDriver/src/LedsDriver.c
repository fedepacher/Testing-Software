#include "LedsDriver.h"

enum {LEDS_ON = ~0, LEDS_OFF = ~LEDS_ON};
enum {FIRST_LED = 1, LAST_LED = 16};

static uint16_t * leds_address;
static uint16_t leds_img;

static uint16_t convertLedNumberToBit(int ledNumbre){
    return 1 << (ledNumbre - 1);
}


static void updateHardware(void){
    *leds_address = leds_img;
}

static bool isLedOutOfBounds(int ledNumbre){
    return (ledNumbre < FIRST_LED || ledNumbre > LAST_LED);
}

static void setLedImageBit(int ledNumber){
    leds_img |= convertLedNumberToBit(ledNumber);
}

static void cleaerLedImageBit(int ledNumber){
    leds_img &= ~(convertLedNumberToBit(ledNumber));
}


void LedsDriver_Constructor(uint16_t * port_address){
    leds_address = port_address;
    leds_img = LEDS_OFF;
    *port_address = leds_img;
    
}

void LedsDriver_Destructor(void){


}

void LedsDriver_On(int led){
    if(isLedOutOfBounds(led))
        return;

    setLedImageBit(led);
    updateHardware();
}


void LedsDriver_Off(int led){
    if(isLedOutOfBounds(led))
        return;
    cleaerLedImageBit(led);
    updateHardware();
}

void LedsDriver_AllOn(){
    leds_img = LEDS_ON;
    updateHardware();
}

void LedsDriver_AllOff(){
    leds_img = LEDS_OFF;
    updateHardware();
}

bool LedsDriver_IsOn(int led){
    if(isLedOutOfBounds(led))
        return false;
    return leds_img & (convertLedNumberToBit(led)); 
}

bool LedsDriver_IsOff(int led){
    return !LedsDriver_IsOn(led); 
    //return false;
}