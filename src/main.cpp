#include <Arduino.h>

const uint16_t BLINKING_WINDOW = 4500; // 4.5 seconds
const float BLINKING_INTERVAL = 0.25; // 0.25s blinking
const float ACCELERATION_THRESHOLD = 0.5 * 9.81; // 0.5g

enum breaking {
    NORMAL_BRAKING,
    HARD_BRAKING,
};

breaking state;
uint16_t hard_braking_start;

void setup() {
    // Setup Accelerometer
    // Init state machine
    state = NORMAL_BRAKING;
}

float readAcceleration();
void turnOnBrakeLight();
void toggleBrakeLight();
void turnOffBrakeLight();

// If the acceleration is greater than 1.5g, then we are braking hard
// If we are breaking hard, make the LED blink at 4Hz for 4.5 seconds then go back to normal
void loop() {
    float acceleration = readAcceleration();

    switch (state) {
        
        case NORMAL_BRAKING:
            if (acceleration < ACCELERATION_THRESHOLD) break; // or return
            
            state = HARD_BRAKING;
            hard_braking_start = millis();

            break;

        case HARD_BRAKING:

            if (millis() - hard_braking_start > BLINKING_WINDOW && acceleration < ACCELERATION_THRESHOLD) {
                state = NORMAL_BRAKING;
                break; // or return
            }


            if (millis() % int (BLINKING_INTERVAL * 1000) < BLINKING_INTERVAL * 500) {
                // Turn on LED
            } else {
                // Turn off LED
            }
            break;
    }
}

float readAcceleration() {
    return 0;
}

void turnOnBrakeLight() {}
void toggleBrakeLight() {}
void turnOffBrakeLight() {}