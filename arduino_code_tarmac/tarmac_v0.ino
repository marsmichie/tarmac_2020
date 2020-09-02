// number of LEDs + Pins assigned
#define NUM_LEDS 16
#define ON_   LOW
#define OFF_  HIGH
// teensy 3.2 for 9 Pins
//uint8_t led_pins[NUM_LEDS] = {8,17,9,16,10,15,11,14,12}; 

// teensy 3.6
//uint8_t led_pins[NUM_LEDS] = {2,3,4,5,6,7,8,9};
uint8_t led_pins[NUM_LEDS] = {30,2,31,3,28,5,29,4,25,9,24,7,26,6,27,8};
/* Pin Teensy ---map---> Relais
 * 31-13  9-5
 * 30-14  8-7
 * 29-15  7-8
 * 28-16  6-6
 * 27-9   5-2
 * 26-10  4-4
 * 25-11  3-1
 * 24-12  2-3
 * 3, 5, 2, 4, 9, 6, 8, 7,27,26,25,24,31,30,29,28
 * 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16
 * 4, 6, 2, 8,10,14,16,12,15,13, 9,11, 3, 1, 7, 5
*/
// Poti für switch (Messmethode)
#define POT_SWITCH A0
#define NUM_CASES 3
#define MQ3_LED 37
#define FSR_LED 38
#define TEMP_LED 39
#define MOT_SEN A3

// turn light on/off
void on(uint8_t n) {digitalWrite(led_pins[n], ON_);}
void off(uint8_t n) {digitalWrite(led_pins[n], OFF_);}

#define UNTRIG_CASES 9
#define TRIG_CASES 8
#define UNTRIG_ANTI 8
bool PIR_before = false;
bool check_PIR() { return digitalRead(MOT_SEN);}
int value, counter;
int untrig_mode = 1, trig_mode = 1, untrig_ant = 1;
// number of led_stripe where sensor is
uint8_t sensor_at_led_stripe_number = 0;

// check pir sensor while waiting
bool delay_pir_check(int delay_) {
    int delay_count = 0;
    while (delay_count < delay_) {
        delay(10);
        if (check_PIR()) {return true;}
        delay_count += 10;
    }
    return false;
}
/*
 * set all lights to low
 */
void turn_off_leds () {
  for (int i=NUM_LEDS-1; i>=0; i--) {
        digitalWrite(led_pins[i], OFF_);
        delay(1);
      }   
}

#include "led_functions.h"
#include "triggered.h"
#include "untriggered.h"

void setup() {
    for (int i=0; i<NUM_LEDS; i++) pinMode(led_pins[i], OUTPUT);
    delay(10);
    for (int i=0; i<NUM_LEDS; i++) digitalWrite(led_pins[i], OFF_);

    randomSeed(analogRead(A5));
    Serial.begin(115200);

    pinMode(FSR_LED, OUTPUT);
    pinMode(TEMP_LED, OUTPUT);

    pinMode(MOT_SEN, INPUT);
    counter = 0;
    //check if microcontroller is running -> green LED 
    digitalWrite(FSR_LED, HIGH);
    
    delay(5000);
    // turn all on at start 
    standard_all_on_up(300);
    delay(3000);
    turn_off_leds();
    standard_all_on_up(300);
    delay(5000);
    
    untrig_mode = random(UNTRIG_CASES)+1;
    trig_mode   = random(TRIG_CASES)+1;
    untrig_ant  = random(UNTRIG_ANTI)+1;
}



void loop()
{  
    digitalWrite(FSR_LED, HIGH);
    delay(50);
    if (counter > 100) {
        counter = 0;
        // change lighting mode after certain number of repetitions
        untrig_mode = random(UNTRIG_CASES)+1;
        trig_mode = random(TRIG_CASES)+1;
        untrig_ant  = random(UNTRIG_ANTI)+1;
    }
    // check if motion sensor was active before
    if (PIR_before) {
        delay(100);
        // PIR is always HIGH -> either defect or not connected
        // just random lights without trigger
        untriggered(untrig_mode);
        PIR_before = check_PIR();

    }
    
    else {
        // motion detected
        if (PIR_before) {
            triggered(trig_mode);
        }
        else { // no motion detected
            digitalWrite(TEMP_LED, HIGH);
            untriggered_antcipated(untrig_ant);
            digitalWrite(TEMP_LED, LOW);
        }
        PIR_before = check_PIR();
    }
    // check if PIR motion sensor is detecting something
    if(check_PIR()) digitalWrite(TEMP_LED, HIGH);
    else digitalWrite(TEMP_LED, LOW);
    delay(5);
}






