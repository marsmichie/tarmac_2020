void blinking_one_ant(uint8_t no_led, int delay_) {
    turn_off_leds();
    for (int i=0; i<50; i++) {
        on(no_led);
        if (delay_pir_check(delay_)) {
digitalWrite(FSR_LED, LOW);
delay(100);            
            triggered(trig_mode);
            return;
        }

        off(no_led);
        if (delay_pir_check(delay_)) {
            triggered(trig_mode);
            return;
        }
    }
}

void random_single_lights_ant(int delay_) {
    turn_off_leds();
    delay(10);
    digitalWrite(led_pins[random(NUM_LEDS)],ON_);
    if (delay_pir_check(delay_)) triggered(trig_mode); 
}

void random_fade_lights_ant(int delay_, int overlap) {
    int r = random(NUM_LEDS);
    on(r);
    if (delay_pir_check(overlap)) triggered(trig_mode); 
    for (int i=NUM_LEDS-1; i>=0; i--) {
        if (i != r) off(i);
        delay(1);
      }
    if (delay_pir_check(delay_)) triggered(trig_mode); 
}

void wave_lights_ant(uint8_t plus_minus, uint16_t delay_) {
    turn_off_leds();
    for (int i=-plus_minus; i<NUM_LEDS+plus_minus; i++) {
        for (int ii=i-plus_minus; ii<=i+plus_minus; ii++) {
            if(ii >= 0 and ii < NUM_LEDS) on(ii);
        }
        for (int ii=0; ii<i-plus_minus; ii++) off(ii); 
        if (delay_pir_check(delay_)) {
            triggered(trig_mode);
            return;
        }
    }
}

void constant_one_ant(int n, int delay_) {
    turn_off_leds();
    on(n);
    if (delay_pir_check(delay_)) triggered(trig_mode); 
}

void random_all_on_off_ant(int delay_) {
  turn_off_leds();
  bool blocked[NUM_LEDS];
  for (int i=0; i<NUM_LEDS; i++) blocked[i] = false;
  for (int i=0; i<NUM_LEDS; i++) {
     int r = random(NUM_LEDS);
     while (blocked[r]) {r = (r+1) % NUM_LEDS;}
     blocked[r] = true;
     on(r);
     if (delay_pir_check(delay_)) {
         triggered(trig_mode);
         return;
     }
  }
  // now turn them off
  for (int i=0; i<NUM_LEDS; i++) {
     int r = random(NUM_LEDS);
     while (!blocked[r]) {r = (r+1) % NUM_LEDS;}
     blocked[r] = false;
     off(r);
     if (delay_pir_check(delay_)) {
         triggered(trig_mode);
         return;
     }
  }
}

void double_up_ant(int delay_) {
    for (int i=0; i<NUM_LEDS; i++) {
        turn_off_leds();
        on(i);
        if (i<(NUM_LEDS-2)) on(i+2);
        if (delay_pir_check(delay_)) {
         triggered(trig_mode);
         return;
     }
    }
}
void wave_backwards_ant(uint8_t plus_minus, int delay_) {
  turn_off_leds();
  for (int i=NUM_LEDS+plus_minus-1; i>= -plus_minus; i--) {
    for (int ii=i+plus_minus; ii>=i-plus_minus; ii--) {
      if(ii >= 0 and ii < NUM_LEDS) on(ii);
    }
    for (int ii=NUM_LEDS-1; ii>=i+plus_minus; ii--) off(ii); 
    if (delay_pir_check(delay_)) {
         triggered(trig_mode);
         return;
    }
  }
}
/*
 * functions running while waiting beeing triggered
 */
void untriggered_antcipated(int mode) {
    switch(mode) {
        case 1:
            blinking_one_ant(sensor_at_led_stripe_number,1000);
            counter += 5;
            break;
        // fast random single
        case 2:
            //random_single_lights_ant(150);
            wave_backwards_ant(0,300);
            counter++;
            break;
        // slow random single
        case 3:
            wave_lights_ant(0,300);
            wave_backwards_ant(0,300);
            //random_single_lights_ant(5000);
            //counter += 10;
            counter++;
            break;
        // small overlap random
        case 4:
            random_fade_lights_ant(500,1000);
            counter += 10;
            break;
        case 5:
            wave_lights_ant(0,600);
            wave_backwards_ant(0,300);
            counter++;
            break;
        case 6:
            constant_one_ant(sensor_at_led_stripe_number,1000);
            counter += 5;
            break;
        case 7:
            random_all_on_off_ant(2000);
            counter += 5;
            break;
        case 8:
            double_up_ant(200);
            counter++;
            break;
        default:
            blinking_one_ant(sensor_at_led_stripe_number,1000);
            break;
    }
}


/*
 * functions that run WITHOUT being triggered by the motion sensor
 */
void untriggered(int mode) {
    switch (mode) {
        // fast random single
        case 1:
            random_single_lights(50);
            counter++;
            break;
        // slow random single
        case 2:
            random_single_lights(5000);
            counter += 10;
            break;
        // small overlap random
        case 3:
            random_fade_lights(500,1000);
            counter += 10;
            break;
        case 4:
            random_all_on_off(2000);
            counter += 5;
            break;
        case 5:
            wave_lights(1,500);
            counter++;
            break;
        case 6:
            wave_lights(0,100);
            counter++;
            break;
        case 7:
            blinking_one(random(NUM_LEDS),1000);
            counter++;
            break;
        case 8:
            constant_one(random(NUM_LEDS),10000);
            counter += 10;
        case 9:
            random_all_on_off_fast_out(2000);
            counter += 5;
            break;
        default:
            random_all_on_off(2000);
            counter += 5;
            break;
    }
}
 
