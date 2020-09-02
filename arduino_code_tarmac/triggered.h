 void wechselseitig_an(int start_led_no, int delay_) {
     turn_off_leds();
     on(start_led_no);
     delay(delay_);
     for (int i=1; i<=int(NUM_LEDS/2); i++) {
            on((start_led_no+i)%NUM_LEDS);
            delay(delay_);
            on((start_led_no-i)%NUM_LEDS);
            delay(delay_);
     }
}

void standard_all_on_up(int delay_) {
    turn_off_leds();
    for (int i=0; i<NUM_LEDS; i++) {
        on(i);
        delay(delay_);
    }
}

void turn_off_down(int delay_) {
    for (int i=NUM_LEDS-1; i>=0; i--) {
        off(i);
        delay(delay_);
    }
}

void turn_off_random(int delay_) {
    bool blocked[NUM_LEDS];
    for (int i=0; i<NUM_LEDS; i++) blocked[i] = true;
    // now turn them off
    for (int i=0; i<NUM_LEDS; i++) {
        int r = random(NUM_LEDS);
        while (!blocked[r]) {r = (r+1) % NUM_LEDS;}
        blocked[r] = false;
        off(r);
        delay(delay_);
    }
}

void turn_on_random(int n) {
    turn_off_leds();
    on(n);
    delay(3000);
}

void wave(int delay_) {
    wave_lights(1,delay_);
}
 /*
 * functions that run after being triggered by the motion sensor
 */
void triggered(int mode) {
    switch (mode) {
        // fast random single
        case 1:
//            wechselseitig_an(sensor_at_led_stripe_number,200);
//            turn_off_random(100);
            delay(500);
            counter += 5;
            break;
        case 2:
            random_all_on_off_fast_out(150);
            counter += 2;
            break;
        case 3:
            wave_lights(0,200);
            wave_backwards(0,200);
            //random_all_on_off(200);
            counter++;
            break;
        case 4:
            standard_all_on_up(200);
            turn_off_down(100);
            counter++;
            break;
        case 5:
            standard_all_on_up(200);
            turn_off_random(100);
            counter++;
            break;
        case 6:
            wave(200);
            wave_backwards(1,200);
            counter++;
            break;
        case 7:
            wave_backwards(1,200);
            wave(200);
//          turn_on_random(random(NUM_LEDS));
            counter++;
            break;
        case 8:
            wave(200);
            wave(200);
            wave(200);
            counter += 2;
            break;
        default:
            random_all_on_off(2000);
            counter += 5;
            break;
    }
    PIR_before = check_PIR();
}

