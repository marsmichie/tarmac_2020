/*
 * functions for leds
 */
void blinking_one(uint8_t led_no, int delay_) {
    turn_off_leds();
    delay(5);
    for (int i=0; i<10; i++) {on(led_no); delay(delay_);}
}

void constant_one(uint8_t led_no, int delay_) {
    turn_off_leds();
    delay(5);
    on(led_no);
    delay(delay_);
}

void random_single_lights(int delay_) {
    turn_off_leds();
    delay(10);
    digitalWrite(led_pins[random(NUM_LEDS)],ON_);
    delay(delay_);
}

void random_fade_lights(int delay_, int overlap) {
    int r = random(NUM_LEDS);
    digitalWrite(led_pins[r],ON_);
    delay(overlap);
    for (int i=NUM_LEDS-1; i>=0; i--) {
        if (i != r) digitalWrite(led_pins[i], OFF_);
        delay(1);
      }
    delay(delay_);
} 

void wave_lights(uint8_t plus_minus, uint16_t delay_) {
  turn_off_leds();
  for (int i=-plus_minus; i<NUM_LEDS+plus_minus; i++) {
    for (int ii=i-plus_minus; ii<=i+plus_minus; ii++) {
      if(ii >= 0 and ii < NUM_LEDS) on(ii);
    }
    for (int ii=0; ii<i-plus_minus; ii++) off(ii); 
    delay(delay_);
  }
}

void wave_backwards(uint8_t plus_minus, int delay_) {
  turn_off_leds();
  for (int i=NUM_LEDS+plus_minus-1; i>= 0-plus_minus; i--) {
    for (int ii=i+plus_minus; ii>=i-plus_minus; ii--) {
      if(ii >= 0 and ii < NUM_LEDS) on(ii);
    }
    for (int ii=NUM_LEDS-1; ii>(i+plus_minus); ii--) off(ii); 
    delay(delay_);
  }
}

void random_all_on_off (int delay_) {
  turn_off_leds();
  bool blocked[NUM_LEDS];
  for (int i=0; i<NUM_LEDS; i++) blocked[i] = false;
  for (int i=0; i<NUM_LEDS; i++) {
     int r = random(NUM_LEDS);
     while (blocked[r]) {r = (r+1) % NUM_LEDS;}
     blocked[r] = true;
     on(r);
     delay(delay_); // entweder auf delay warten oder falls schneller pir
  }
  // now turn them off
  for (int i=0; i<NUM_LEDS; i++) {
     int r = random(NUM_LEDS);
     while (!blocked[r]) {r = (r+1) % NUM_LEDS;}
     blocked[r] = false;
     off(r);
     delay(delay_);
  }
}
void random_all_on_off_fast_out(int delay_) {
  turn_off_leds();
  bool blocked[NUM_LEDS];
  for (int i=0; i<NUM_LEDS; i++) blocked[i] = false;
  for (int i=0; i<NUM_LEDS; i++) {
     int r = random(NUM_LEDS);
     while (blocked[r]) {r = (r+1) % NUM_LEDS;}
     blocked[r] = true;
     on(r);
     delay(delay_); // entweder auf delay warten oder falls schneller pir
  }
  // now turn them off
  for (int i=0; i<NUM_LEDS; i++) {
     int r = random(NUM_LEDS);
     while (!blocked[r]) {r = (r+1) % NUM_LEDS;}
     blocked[r] = false;
     off(r);
     delay(100);
  }
}
